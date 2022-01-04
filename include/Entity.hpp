#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Maths.hpp"

class Entity
{
    public:
        Entity(Vector2f pos, SDL_Texture* entity_texture, int texture_width, int texture_height);
        Vector2f& getPosition();
        void setPosition(Vector2f position);
        void changePosition(Vector2f delta_pos);
        SDL_Texture* getTexture();
        std::pair<SDL_Rect, Vector2f>& getCurrentFrame(int index = 0);
        int getCurrentFrameLength();
        void addTileToCurrentFrame(int tile_x, int tile_y, int x_offset, int y_offset);

    protected:
        Vector2f position;

    private:
        SDL_Texture* texture;
        std::vector<std::pair<SDL_Rect, Vector2f>> current_frame;
};
