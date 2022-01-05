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
        Player(SDL_Texture* player_texture);
        void move();
        void jump();
        void setDirection(std::string dir);

    private:
        std::string direction;
        Vector2f velocity;
        bool can_jump = false;
        bool jump_input = false;
};
