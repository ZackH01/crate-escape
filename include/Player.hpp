#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "Entity.hpp"
#include "Maths.hpp"

class Player: public Entity
{
    public:
        Player(Vector2f position, SDL_Texture* player_texture, int width, int height);
        void move();
        void setDirection(std::string dir);

    private:
        std::string direction;
        Vector2f velocity;
};
