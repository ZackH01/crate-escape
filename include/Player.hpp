#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include "Maths.hpp"
#include "Entity.hpp"
#include "Crate.hpp"
#include "GoalPlatform.hpp"

class Player: public Entity
{
    public:
        Player(SDL_Texture* player_texture);
        void move(std::vector<Crate>& crate_vect, GoalPlatform& goal);
        void jump();
        void setDirection(std::string dir);
        bool& isLevelClear();
        bool& isGameOver();

    private:
        std::string direction;
        Vector2f velocity;
        float current_crate_velocity;
        bool can_jump;
        bool jump_input;
        bool can_land_on_platform;
        bool level_clear;
        bool game_over;
};
