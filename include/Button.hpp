#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Maths.hpp"
#include "Text.hpp"

class Button
{
    public:
        Button();
        Button(SDL_Texture* b_t, Text t, Vector2f pos, int w, int h);
        Button(SDL_Texture* b_t, TTF_Font* f, std::string t, SDL_Renderer* r, Vector2f pos, int w, int h);
        int getWidth();
        int getHeight();
        Vector2f getPosition();
        void setPosition(Vector2f pos);
        Text getText();
        void setText(Text t);
        SDL_Texture* getBackgroundTexture();
        void setBackgroundTexture(SDL_Texture* b_t);

    private:
        int width;
        int height;
        Vector2f position;
        Text text;
        SDL_Texture* background_texture;
};
