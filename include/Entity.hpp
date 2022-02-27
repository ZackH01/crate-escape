#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Maths.hpp"

class Entity
{
    public:
        Entity(SDL_Texture* e_texture, Vector2f pos, int e_width, int e_height, int t_width, int t_height);
        Entity(SDL_Texture* e_texture, Vector2f pos, int e_width, int e_height);
        Vector2f getPosition();
        void setPosition(Vector2f position);
        void changePosition(Vector2f delta_pos);
        SDL_Texture* getTexture();
        int getWidth();
        int getHeight();
        std::pair<SDL_Rect, Vector2f>& getCurrentFrame(int index = 0);
        int getCurrentFrameLength();
        HitboxRect& getHitboxSize();
        HitboxRect getHitbox();
        bool checkCollision(Entity& entity);

    protected:
        void setSize(int width, int height);
        void addTileToCurrentFrame(int tile_x, int tile_y, int x_offset, int y_offset);
        void setHitbox(float x_offset, float y_offset, float width, float height);
        Vector2f position;

    private:
        SDL_Texture* texture;
        EntDim size;
        EntDim tile_size;
        std::vector<std::pair<SDL_Rect, Vector2f>> current_frame;
        HitboxRect hitbox;
};
