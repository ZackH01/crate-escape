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
        void render(SDL_Texture* texture, int x1, int y1, int x2, int y2);
        void render(Entity& entity);
        void display();
        void clear();
        bool isRunning();
        void exitWindow();
        void close();

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        bool running;
};
