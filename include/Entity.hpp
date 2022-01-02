#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Maths.hpp"

class Entity
{
    public:
        Entity(Vector2f pos, SDL_Texture* entity_texture, int texture_width, int texture_height);
        Vector2f& getPosition();
        SDL_Texture* getTexture();
        SDL_Rect getCurrentFrame();
        void setPosition(Vector2f position);
        void changePosition(Vector2f delta_pos);

    protected:
        Vector2f position;

    private:
        SDL_Texture* texture;
        SDL_Rect current_frame;
};
