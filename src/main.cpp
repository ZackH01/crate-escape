#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "RenderWindow.hpp"
#include "Maths.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Crate.hpp"
#include "GoalPlatform.hpp"

RenderWindow window("Crate Escape", 1280, 720);
SDL_Texture* background;
SDL_Texture* top_cover_texture;
SDL_Texture* player_texture;
SDL_Texture* crate_texture;
SDL_Texture* platform_texture;

Player player(player_texture);
std::vector<Crate> crates;
GoalPlatform goal(platform_texture, 0);

bool running;
SDL_Event event;
int timer;
int level;
int crate_frequency;
float crate_speed;

void loadTextures()
{
    background = window.loadTexture("res/graphics/background.png");
    top_cover_texture = window.loadTexture("res/graphics/top_cover.png");
    player_texture = window.loadTexture("res/graphics/player.png");
    crate_texture = window.loadTexture("res/graphics/crate.png");
    platform_texture = window.loadTexture("res/graphics/platform.png");
}

void resetGame()
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
    player = Player(player_texture);
    crates.clear();
    Crate::resetCrateMap();
    goal = GoalPlatform(platform_texture, goal_height);

    std::cout << "Level: " << level << std::endl;
}

void addCrate()
{
    crates.push_back(Crate(crate_texture, player.getPosition().x, crate_speed));
}

void update()
{
    //Add extra crates
    if(timer % crate_frequency == 0)
    {
        addCrate();
    }

    //Move entities
    for(Crate& c: crates)
    {
        c.move(crates);
    }
    player.move(crates, goal);

    //Check for game reset
    if(player.isGameOver())
    {
        level = 1;
        resetGame();
    }
    else if(player.isLevelClear())
    {
        level++;
        resetGame();
    }

    //Refresh window
    window.clear();

    window.render(background);
    window.render(player);
    for(Entity& c: crates)
    {
        window.render(c);
    }
    window.render(goal);
    window.render(top_cover_texture, 400, 0, 880, 33);

    window.display();
}

void handleEvents()
{
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                running = false;
                break;

            //Keyboard events
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    //Up arrow - jump
                    case SDLK_UP:
                        player.jump();
                        break;

                    //Right arrow - move right
                    case SDLK_RIGHT:
                        player.setDirection("right");
                        break;

                    //Left arrow - move left
                    case SDLK_LEFT:
                        player.setDirection("left");
                        break;
                }
                break;

            case SDL_KEYUP:
                switch(event.key.keysym.sym)
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
}

int main(int argc, char* argv[])
{
    //Initialise SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL Init failed. Error: " << SDL_GetError() << std::endl;
        return 0;
    }

    if(!(IMG_Init(IMG_INIT_PNG)))
    {
        std::cout << "IMG Init failed. Error: " << SDL_GetError() << std::endl;
        return 0;
    }

    //Set RNG Seed based on the time of the user's device
    std::time_t device_time;
    std::time(&device_time);
    std::srand(device_time);

    //Initialise game
    loadTextures();
    level = 1;
    resetGame();

    running = true;
    timer = 0;

    //Event loop
    while(running)
    {
        handleEvents();
        update();

        timer++;
        SDL_Delay(1000/60);
    }

    //Close SDL
    window.close();
    SDL_Quit();

    return 0;
}
