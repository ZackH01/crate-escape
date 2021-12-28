#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* title, int width, int height)
:window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if(window == NULL)
        std::cout << "Failed to create window. Error: " << SDL_GetError() << std::endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* file_path)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, file_path);
    if(texture == NULL)
        std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

    return texture;
}

void RenderWindow::render(SDL_Texture* texture)
{
    //Renders the given texture over the whole window
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::close()
{
    SDL_DestroyWindow(window);
}
