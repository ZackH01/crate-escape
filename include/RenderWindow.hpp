#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.hpp"

class RenderWindow
{
    public:
        RenderWindow(const char* title, int width, int height);
        SDL_Texture* loadTexture(const char* file_path);
        void render(SDL_Texture* texture);
        void render(Entity& entity);
        void display();
        void clear();
        void close();

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};
