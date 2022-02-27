#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Maths.hpp"
#include "Entity.hpp"
#include "Player.hpp"

class Crate: public Entity
{
    public:
        Crate(SDL_Texture* crate_texture, int player_x_pos, float velocity);
        void move(std::vector<Crate>& crate_vect);
        float& getFallVelocity();
        static void resetCrateMap();

    private:
        bool falling;
        float fall_velocity;
        static int crate_map[18][15];
        static void printCrateMap();
};
