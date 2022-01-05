#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Maths.hpp"
#include "Player.hpp"
#include "Crate.hpp"

int main(int argc, char* argv[])
{
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

    //Create window
    RenderWindow window("Crate Escape", 1280, 720);

    //Load textures
    SDL_Texture* background = window.loadTexture("res/graphics/background.png");
    SDL_Texture* player_texture = window.loadTexture("res/graphics/player.png");
    SDL_Texture* crate_texture = window.loadTexture("res/graphics/crate.png");

    //Entities
    Player player(player_texture);
    Crate test_crate(crate_texture, 3, 2);

    //Game loop
    bool running = true;
    SDL_Event event;

    while(running)
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
                        //Up arrow
                        case SDLK_UP:
                            player.jump();
                            break;

                        //Right arrow
                        case SDLK_RIGHT:
                            player.setDirection("right");
                            break;

                        //Left arrow
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

        //Move entities
        player.move();

        //Refresh window
        window.clear();
        window.render(background);
        window.render(player);
        window.render(test_crate);
        window.display();

        SDL_Delay(1000/60);
    }

    //Close SDL
    window.close();
    SDL_Quit();

    return 0;
}
