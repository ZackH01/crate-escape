#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include "RenderWindow.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "Crate.hpp"
#include "GoalPlatform.hpp"

Game::Game(RenderWindow* w)
:player(Player(NULL)), goal(GoalPlatform(NULL, 0))
{
    window = w;
    loadGameTextures();

    level = 1;
    score = 0;
    resetGame();
}

void Game::gameLoop(SDL_Event e)
{
    //Handle events
    while(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            //Close window event
            case SDL_QUIT:
                window->exitWindow();
                return;

            //Keyboard events
            case SDL_KEYDOWN:
                switch(e.key.keysym.sym)
                {
                    //Up arrow -> jump
                    case SDLK_UP:
                        player.jump();
                        break;

                    //Right arrow -> move right
                    case SDLK_RIGHT:
                        player.setDirection("right");
                        break;

                    //Left arrow -> move left
                    case SDLK_LEFT:
                        player.setDirection("left");
                        break;
                }
                break;

            case SDL_KEYUP:
                switch(e.key.keysym.sym)
                {
                    //Right arrow
                    case SDLK_RIGHT:
                        player.setDirection("none");
                        break;

                    //Left arrow
                    case SDLK_LEFT:
                        player.setDirection("none");
                        break;
                }
                break;
        }
    }

    //Add extra crates
    if(time % crate_frequency == 0)
    {
        addCrate();
    }

    //Move entities
    for(Crate& c: crates)
    {
        c.move(crates);

        //If the player has jumped onto a falling crate, add to the score
        if(c.isFalling() && c.hasBeenJumpedOn() && !c.hasAddedPoints())
        {
            int crate_score_multiplier = c.getFallVelocity()-2;
            score += 5 * crate_score_multiplier * (c.getHeight()/32);
            c.setToAddedPoints();

            std::cout << "+" << 5 * crate_score_multiplier * (c.getHeight()/32) << std::endl;
        }
    }
    player.move(crates, goal);

    //Check for game reset
    if(player.isGameOver())
    {
        level = 1;
        score = 0;
        resetGame();
    }
    else if(player.isLevelClear())
    {
        //Add score for clearing a level
        int clear_bonus = 1000;
        if(level < 5)
        {
            clear_bonus += 250 * (level-1);
        }
        else
        {
            clear_bonus += 500 * level;
        }

        //Add score for every second below 60 seconds
        int time_bonus = 60 - time/60;
        switch(level)
        {
            case 1:
                time_bonus *= 5;
                break;
            case 2:
                time_bonus *= 10;
                break;
            case 3:
                time_bonus *= 20;
                break;
            case 4:
                time_bonus *= 30;
                break;
            default:
                time_bonus *= 50;
                break;
        }
        //Never deduct points
        if(time_bonus < 0)
        {
            time_bonus = 0;
        }

        score += clear_bonus;
        score += time_bonus;

        std::cout << "Clear Bonus: " << clear_bonus << std::endl;
        std::cout << "Time: " << time/60 << " seconds" << std::endl;
        std::cout << "Time Bonus: " << time_bonus << std::endl << std::endl;

        level++;
        resetGame();
    }

    time++;
    renderGame();
}

void Game::addCrate()
{
    crates.push_back(Crate(crate_texture, player.getPosition().x, crate_speed));
}

void Game::resetGame()
{
    //Set variables for game difficulty
    int goal_height = 96;

    //Goal gets further away for the first 5 levels
    if(level < 5)
    {
        goal_height += (5-level)*64;
    }

    //Crate speeds and frequencies for each level
    if(level <= 5)
    {
        //Sharper increase in difficulty for levels 1, 2 and 3
        if(level == 1)
        {
            crate_speed = 3.5f;
            crate_frequency = 150;
        }
        else if(level == 2)
        {
            crate_speed = 3.75f;
            crate_frequency = 135;
        }
        else
        {
            crate_speed = 4.0f;
            crate_frequency = 120;
        }
    }
    else if(level < 15)
    {
        crate_speed = 4.0f;
        crate_frequency = 120;

        //Difficulty increases linearly after level 5 and until level 15
        if(level % 2 == 0)
        {
            //Increase crate frequency
            crate_frequency -= ((level-5+1)/2) * 15;
        }
        else
        {
            //Increase crate speed
            crate_speed += ((level-5)/2) * 0.25f;
        }
    }
    else
    {
        //Maximum difficulty
        crate_speed = 5.5f;
        crate_frequency = 45;
    }

    //Initialise game objects
    time = 0;
    player = Player(player_texture);
    crates.clear();
    Crate::resetCrateMap();
    goal = GoalPlatform(platform_texture, goal_height);

    std::cout << "Level: " << level << std::endl;
    std::cout << "Score: " << score << std::endl;
}

void Game::renderGame()
{
    window->clear();

    window->render(background);
    window->render(player);
    for(Entity& c: crates)
    {
        window->render(c);
    }
    window->render(goal);
    window->render(top_cover, 400, 0, 880, 33);

    window->display();
}

void Game::loadGameTextures()
{
    background = window->loadTexture("res/graphics/background.png");
    top_cover = window->loadTexture("res/graphics/top_cover.png");
    player_texture = window->loadTexture("res/graphics/player.png");
    crate_texture = window->loadTexture("res/graphics/crate.png");
    platform_texture = window->loadTexture("res/graphics/platform.png");
}
