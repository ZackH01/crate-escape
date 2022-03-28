#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Maths.hpp"

class Text
{
    public:
        Text();
        Text(TTF_Font* f, std::string t, Vector2f pos, SDL_Renderer* r);
        TTF_Font* getFont();
        std::string getText();
        void setText(std::string t);
        SDL_Colour getColour();
        void setColour(int red, int green, int blue, int alpha);
        Vector2f getPosition();
        SDL_Texture* getTexture();

    private:
        void updateTexture();
        TTF_Font* font;
        std::string text;
        SDL_Colour colour;
        Vector2f position;
        SDL_Texture* texture;
        SDL_Renderer* renderer;
};
