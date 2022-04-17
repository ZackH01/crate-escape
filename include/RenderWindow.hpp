#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.hpp"
#include "Text.hpp"
#include "Button.hpp"

class RenderWindow
{
    public:
        RenderWindow(const char* title, int width, int height);
        SDL_Texture* loadTexture(const char* file_path);
        TTF_Font* loadFont(const char* file_path, int font_size);
        void render(SDL_Texture* texture);
        void render(SDL_Texture* texture, int x1, int y1, int x2, int y2);
        void render(Entity& entity);
        void render(Text& text);
        void render(Button& button);
        void display();
        void clear();
        SDL_Renderer* getRenderer();
        bool isRunning();
        void exitWindow();
        void close();

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        bool running;
};
