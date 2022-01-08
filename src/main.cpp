#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "RenderWindow.hpp"
#include "Maths.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Crate.hpp"

RenderWindow window("Crate Escape", 1280, 720);
SDL_Texture* background;
SDL_Texture* top_cover_texture;
SDL_Texture* player_texture;
SDL_Texture* crate_texture;

Player player(player_texture);
std::vector<Crate> crates;

bool running;
SDL_Event event;
int time;

void loadTextures()
{
    background = window.loadTexture("res/graphics/background.png");
    top_cover_texture = window.loadTexture("res/graphics/top_cover.png");
    player_texture = window.loadTexture("res/graphics/player.png");
    crate_texture = window.loadTexture("res/graphics/crate.png");
}

void resetGame()
{
    player = Player(player_texture);
    crates.clear();
}

void addCrate()
{
    //Frequency of the sizes of crates
    int crate_widths[10] = {1, 2, 2, 2, 3, 3, 3, 3, 4, 4};
    int crate_heights[10] = {1, 2, 2, 2, 2, 3, 3, 3, 3, 4};

    crates.push_back(Crate(crate_texture, crate_widths[std::rand()%10], crate_heights[std::rand()%10]));
}

void update()
{
    //Add extra crates
    if(time % 120 == 0)
    {
        addCrate();
    }

    //Move entities
    for(Crate& c: crates)
    {
        c.move(crates);
    }
    player.move(crates);

    //Check for game reset
    if(player.isGameOver())
    {
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
    window.render(top_cover_texture, 400, 0, 880, 113);

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

                    //R key - reset game
                    case SDLK_r:
                        resetGame();
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

    //Initialise game
    loadTextures();
    resetGame();

    running = true;
    time = 0;

    //Event loop
    while(running)
    {
        handleEvents();
        update();

        time++;
        SDL_Delay(1000/60);
    }

    //Close SDL
    window.close();
    SDL_Quit();

    return 0;
}
