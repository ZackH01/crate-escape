#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include "Entity.hpp"
#include "Maths.hpp"
#include "Crate.hpp"

class Player: public Entity
{
    public:
        Player(SDL_Texture* player_texture);
        void move(std::vector<Crate>& crate_vect);
        void jump();
        void setDirection(std::string dir);

    private:
        std::string direction;
        Vector2f velocity;
        bool can_jump = false;
        bool jump_input = false;
};
