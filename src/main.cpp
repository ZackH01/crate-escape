#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Maths.hpp"
#include "RenderWindow.hpp"
#include "Game.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Crate.hpp"
#include "GoalPlatform.hpp"

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

    //Initialise the window and game
    RenderWindow window("Crate Escape", 1280, 720);
    Game game = Game(&window);

    //Main loop
    SDL_Event event;
    while(window.isRunning())
    {
        game.gameLoop(event);

        SDL_Delay(1000/60);
    }

    //Close SDL
    window.close();
    SDL_Quit();

    return 0;
}
