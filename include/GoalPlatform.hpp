#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.hpp"

class GoalPlatform: public Entity
{
    public:
        GoalPlatform(SDL_Texture* platform_texture, int y_pos);
};
