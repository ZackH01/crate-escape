#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Maths.hpp"
#include "Entity.hpp"

class Crate: public Entity
{
    public:
        Crate(SDL_Texture* crate_texture, float player_x_pos, float velocity);
        void move(std::vector<Crate>& crate_vect);
        float getFallVelocity();
        bool isFalling();
        void setToJumpedOn();
        bool hasBeenJumpedOn();
        void setToAddedPoints();
        bool hasAddedPoints();
        static void resetCrateMap();

    private:
        bool falling;
        bool jumped_on;
        bool added_points;
        float fall_velocity;
        static int crate_map[18][15];
        static void printCrateMap();
};
