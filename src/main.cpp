#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Maths.hpp"

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

    //Test entity
    Entity test_entity(Vector2f(400, 300), test_texture, 128, 64);

    //Game loop
    bool running = true;
    SDL_Event event;

    while(running)
    {
        //Check events
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
        window.render(test_entity);
        window.display();

        SDL_Delay(1000/60);
    }

    //Close SDL
    window.close();
    SDL_Quit();

    return 0;
}
