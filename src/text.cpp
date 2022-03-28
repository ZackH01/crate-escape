#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Text.hpp"

Text::Text()
{
    font = NULL;
    text = "";
    position = Vector2f();
    texture = NULL;
    renderer = NULL;

    //Default colour is black
    colour.r = 0;
    colour.g = 0;
    colour.b = 0;
    colour.a = 255;
}

Text::Text(TTF_Font* f, std::string t, Vector2f pos, SDL_Renderer* r)
{
    font = f;
    text = t;
    position = pos;
    texture = NULL;
    renderer = r;

    //Default colour is black
    colour.r = 0;
    colour.g = 0;
    colour.b = 0;
    colour.a = 255;

    updateTexture();
}

TTF_Font* Text::getFont()
{
    return font;
}

std::string Text::getText()
{
    return text;
}


void Text::setText(std::string t)
{
    text = t;
    updateTexture();
}

SDL_Colour Text::getColour()
{
    return colour;
}

void Text::setColour(int red, int green, int blue, int alpha)
{
    colour.r = red;
    colour.g = green;
    colour.b = blue;
    colour.a = alpha;

    updateTexture();
}

Vector2f Text::getPosition()
{
    return position;
}

SDL_Texture* Text::getTexture()
{
    return texture;
}

void Text::updateTexture()
{
    if(texture != NULL)
    {
        //Destroy texture if it already exists
        SDL_DestroyTexture(texture);
        texture = NULL;
    }

    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), colour);
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    //Free resources
    SDL_FreeSurface(surface);
}
