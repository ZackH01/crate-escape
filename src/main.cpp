#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Maths.hpp"
#include "Player.hpp"

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
    SDL_Texture* test_texture = window.loadTexture("res/graphics/test.png");

    //Test player entity
    Player test_player(Vector2f(100, 500), test_texture, 128, 64);

    //Game loop
    bool running = true;
    SDL_Event event;

    while(running)
    {
        test_player.move("right");
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running = false;
            }
        }

        //Refresh window
        window.clear();
        window.render(test_player);
        window.display();

        SDL_Delay(1000/60);
    }

    //Close SDL
    window.close();
    SDL_Quit();

    return 0;
}
