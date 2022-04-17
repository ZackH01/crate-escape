#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Maths.hpp"
#include "Button.hpp"

Button::Button()
{
    width = 0;
    height = 0;
    position = Vector2f();
    text = Text();
    position = Vector2f();
}

Button::Button(SDL_Texture* b_t, Text t, Vector2f pos, int w, int h)
{
    width = w;
    height = h;
    position = pos;
    text = t;
    background_texture = b_t;

    //Put text in the middle of the button
    Vector2f text_pos = Vector2f(position.x+(0.5*width)-(0.5*text.getWidth()), position.y+(0.5*height)-(0.5*text.getHeight()));
    text.setPosition(text_pos);
}

Button::Button(SDL_Texture* b_t, TTF_Font* f, std::string t, SDL_Renderer* r, Vector2f pos, int w, int h)
{
    width = w;
    height = h;
    position = pos;
    text = Text(f, t, position, r);
    background_texture = b_t;

    //Put text in the middle of the button
    Vector2f text_pos = Vector2f(position.x+(0.5*width)-(0.5*text.getWidth()), position.y+(0.5*height)-(0.5*text.getHeight()));
    text.setPosition(text_pos);
}

int Button::getWidth()
{
    return width;
}

int Button::getHeight()
{
    return height;
}

Vector2f Button::getPosition()
{
    return position;
}

void Button::setPosition(Vector2f pos)
{
    position = pos;

    //Put text in the middle of the button
    Vector2f text_pos = Vector2f(position.x+(0.5*width)-(0.5*text.getWidth()), position.y+(0.5*height)-(0.5*text.getHeight()));
    text.setPosition(text_pos);
}

Text Button::getText()
{
    return text;
}

void Button::setText(Text t)
{
    text = t;
}

SDL_Texture* Button::getBackgroundTexture()
{
    return background_texture;
}

void Button::setBackgroundTexture(SDL_Texture* b_t)
{
    background_texture = b_t;
}
