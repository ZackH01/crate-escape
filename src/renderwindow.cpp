#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "RenderWindow.hpp"
#include "Entity.hpp"

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

void RenderWindow::render(SDL_Texture* texture, int x1, int y1, int x2, int y2)
{
    //Renders the given texture inside the defined rectangle
    SDL_Rect dst;
    dst.x = x1;
    dst.y = y1;
    dst.w = x2-x1;
    dst.h = y2-y1;

    SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void RenderWindow::render(Entity& entity)
{
    for(int i=0; i < entity.getCurrentFrameLength(); i++)
    {
        //Texture source of each tile in the frame
        SDL_Rect src = entity.getCurrentFrame(i).first;

        //Location of the render of each tile in the frame relative to the entity's position
        SDL_Rect dst;
        dst.x = entity.getPosition().x + entity.getCurrentFrame(i).second.x;
        dst.y = entity.getPosition().y + entity.getCurrentFrame(i).second.y;
        dst.w = entity.getCurrentFrame(i).first.w;
        dst.h = entity.getCurrentFrame(i).first.h;

        SDL_RenderCopy(renderer, entity.getTexture(), &src, &dst);
    }
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
