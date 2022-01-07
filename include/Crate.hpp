#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Entity.hpp"
#include "Maths.hpp"

class Crate: public Entity
{
    public:
        Crate(SDL_Texture* crate_texture, int crate_width, int crate_height);
        void move(std::vector<Crate>& crate_vect);
        float& getFallVelocity();

    private:
        bool falling;
        float fall_velocity;
};
