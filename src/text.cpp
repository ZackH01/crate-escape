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

    //Default colour is black
    colour.r = 0;
    colour.g = 0;
    colour.b = 0;
}

Text::Text(TTF_Font* f, std::string t, Vector2f pos)
{
    font = f;
    text = t;
    position = pos;

    //Default colour is black
    colour.r = 0;
    colour.g = 0;
    colour.b = 0;
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
}

SDL_Colour Text::getColour()
{
    return colour;
}

void Text::setColour(int red, int green, int blue)
{
    colour.r = red;
    colour.g = green;
    colour.b = blue;
}

Vector2f Text::getPosition()
{
    return position;
}
