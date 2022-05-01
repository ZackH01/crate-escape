#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include "Constants.hpp"
#include "RenderWindow.hpp"
#include "Game.hpp"
#include "Text.hpp"
#include "Player.hpp"
#include "Crate.hpp"
#include "GoalPlatform.hpp"

using namespace constants;

Game::Game(RenderWindow* w)
:player(Player(NULL)), goal(GoalPlatform(NULL, 0))
{
    window = w;
    loadGameTextures();

    title_text = Text(font_72, "Crate Escape", Vector2f(), window->getRenderer());
    continue_text = Text(font_18, "Press any key to continue", Vector2f(), window->getRenderer());
    level_text = Text(font_36, "Level: ", Vector2f(GAME_TEXT_X_POS, GAME_TEXT_Y_POS), window->getRenderer());
    score_text = Text(font_36, "Score: ", Vector2f(GAME_TEXT_X_POS, GAME_TEXT_Y_POS+36), window->getRenderer());
    paused_text = Text(font_36, "Paused", Vector2f(), window->getRenderer());
    level_clear_text = Text(font_72, "Level Cleared!", Vector2f(), window->getRenderer());
    clear_bonus_text = Text(font_36, "Clear Bonus: +", Vector2f(), window->getRenderer());
    time_bonus_text = Text(font_36, "Time Bonus: +", Vector2f(), window->getRenderer());
    game_over_text = Text(font_72, "Game Over!", Vector2f(), window->getRenderer());
    level_text.setColour(48, 48, 48, 255);
    score_text.setColour(48, 48, 48, 255);
    paused_text.setColour(16, 16, 16, 255);
    level_clear_text.setColour(48, 48, 48, 255);
    clear_bonus_text.setColour(48, 48, 48, 255);
    time_bonus_text.setColour(48, 48, 48, 255);
    game_over_text.setColour(48, 48, 48, 255);
    title_text.setColour(48, 48, 48, 255);
    continue_text.setColour(48, 48, 48, 255);
    title_text.setPosition(Vector2f(SCREEN_CENTRE_X - (title_text.getWidth()/2), 80));
    continue_text.setPosition(Vector2f(SCREEN_CENTRE_X - (continue_text.getWidth()/2), 550));
    paused_text.setPosition(Vector2f(GAME_CENTRE_X - (paused_text.getWidth()/2), GAME_CENTRE_Y - 100));
    game_over_text.setPosition(Vector2f(SCREEN_CENTRE_X - (game_over_text.getWidth()/2), 80));

    state = START_SCREEN;
    level = 1;
    score = 0;
}

void Game::gameLoop(SDL_Event e)
{
    //Handle events
    while(SDL_PollEvent(&e))
    {
        if(state == GAME_RUNNING || state == GAME_PAUSED)
        {
            //Game controls
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

                        //Escape key -> toggle pause
                        case SDLK_ESCAPE:
                            if(state == GAME_RUNNING)
                            {
                                state = GAME_PAUSED;
                            }
                            else
                            {
                                state = GAME_RUNNING;
                            }

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
        else
        {
            //Press any key to continue
            switch(e.type)
            {
                //Close window event
                case SDL_QUIT:
                    window->exitWindow();
                    return;

                //Keyboard events
                case SDL_KEYDOWN:
                    resetGame();
                    break;
            }
        }
    }

    //Update the game if it is not paused or on any transition screen
    if(state == GAME_RUNNING)
    {
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

                updateGameUI();
            }
        }
        player.move(crates, goal);

        //Check for game reset
        if(player.isGameOver())
        {
            state = GAME_OVER;
            score_text.setPosition(Vector2f(SCREEN_CENTRE_X - (score_text.getWidth()/2), 280));
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
            updateGameUI();
            
            level_clear_text.setText("Level " + std::to_string(level) + " Cleared!");
            clear_bonus_text.setText("Clear Bonus:  +" + std::to_string(clear_bonus));
            time_bonus_text.setText("Time Bonus:  +" + std::to_string(time_bonus));
            level_clear_text.setPosition(Vector2f(SCREEN_CENTRE_X - (level_clear_text.getWidth()/2), 80));
            clear_bonus_text.setPosition(Vector2f(SCREEN_CENTRE_X - (clear_bonus_text.getWidth()/2), 280));
            time_bonus_text.setPosition(Vector2f(SCREEN_CENTRE_X - (time_bonus_text.getWidth()/2), 316));
            score_text.setPosition(Vector2f(SCREEN_CENTRE_X - (score_text.getWidth()/2), 370));

            state = LEVEL_CLEAR;
        }

        time++;
    }

    renderGame();
}

void Game::addCrate()
{
    crates.push_back(Crate(crate_texture, player.getPosition().x, crate_speed));
}

void Game::resetGame()
{
    if(state == GAME_OVER || state == START_SCREEN)
    {
        level = 1;
        score = 0;
    }
    else
    {
        level++;
    }

    state = GAME_RUNNING;
    score_text.setPosition(Vector2f(GAME_TEXT_X_POS, GAME_TEXT_Y_POS+36));

    //Set variables for game difficulty
    int goal_height = GAME_TOP_BORDER+64;

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

    updateGameUI();
}

void Game::updateGameUI()
{
    level_text.setText("Level:  " + std::to_string(level));
    score_text.setText("Score: " + std::to_string(score));
}

void Game::renderGame()
{
    window->clear();

    switch(state)
    {
        case START_SCREEN:
            //Render start screen
            window->render(background);
            window->render(title_text);
            window->render(continue_text);
            break;

        case LEVEL_CLEAR:
            //Render level cleared screen
            window->render(background);
            window->render(level_clear_text);
            window->render(clear_bonus_text);
            window->render(time_bonus_text);
            window->render(score_text);
            window->render(continue_text);
            break;

        case GAME_OVER:
            //Render gameover screen
            window->render(background);
            window->render(game_over_text);
            window->render(score_text);
            window->render(continue_text);
            break;

        default:
            //Render main game screen
            window->render(game_background);
            window->render(player);
            for(Entity& c: crates)
            {
                window->render(c);
            }
            window->render(goal);
            window->render(background, GAME_LEFT_BORDER, 0, GAME_RIGHT_BORDER, GAME_TOP_BORDER);

            window->render(level_text);
            window->render(score_text);

            //Show pause text and apply background effect when paused
            if(state == GAME_PAUSED)
            {
                window->render(paused_text);
                window->render(paused_shader, GAME_LEFT_BORDER, GAME_TOP_BORDER, GAME_RIGHT_BORDER, GAME_BOTTOM_BORDER);
            }

            break;
    }

    window->display();
}

void Game::loadGameTextures()
{
    //Load textures from files
    game_background = window->loadTexture("res/graphics/background.png");
    player_texture = window->loadTexture("res/graphics/player.png");
    crate_texture = window->loadTexture("res/graphics/crate.png");
    platform_texture = window->loadTexture("res/graphics/platform.png");
    font_18 = window->loadFont("res/fonts/OpenSans-Regular.ttf", 18);
    font_36 = window->loadFont("res/fonts/OpenSans-Regular.ttf", 36);
    font_72 = window->loadFont("res/fonts/OpenSans-Regular.ttf", 72);

    //Create background texture for transition screens
    SDL_Surface* surface = SDL_CreateRGBSurface(SDL_SWSURFACE, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 221, 221, 221));
    background = SDL_CreateTextureFromSurface(window->getRenderer(), surface);
    SDL_SetTextureBlendMode(background, SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(surface);

    //Create background effect while the game is paused
    surface = SDL_CreateRGBSurface(SDL_SWSURFACE, GAME_WIDTH, GAME_HEIGHT, 32, 0, 0, 0, 0);
    paused_shader = SDL_CreateTextureFromSurface(window->getRenderer(), surface);
    SDL_SetTextureBlendMode(paused_shader, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(paused_shader, 32);
    SDL_FreeSurface(surface);
}
