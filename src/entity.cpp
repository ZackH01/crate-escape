#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Entity.hpp"
#include "Maths.hpp"

Entity::Entity(SDL_Texture* e_texture, Vector2f pos, int e_width, int e_height, int t_width, int t_height)
:position(pos), texture(e_texture)
{
    //Constructor with no initial frame
    size.w = e_width;
    size.h = e_height;
    tile_size.w = t_width;
    tile_size.h = t_height;
}

Entity::Entity(SDL_Texture* e_texture, Vector2f pos, int e_width, int e_height)
:position(pos), texture(e_texture)
{
    //Constructor with initial frame
    size.w = e_width;
    size.h = e_height;
    tile_size.w = e_width;
    tile_size.h = e_height;

    addTileToCurrentFrame(0, 0, 0, 0);
}

Vector2f& Entity::getPosition()
{
    return position;
}

void Entity::setPosition(Vector2f pos)
{
    position = pos;
}

void Entity::changePosition(Vector2f delta_pos)
{
    position.x += delta_pos.x;
    position.y += delta_pos.y;
}

SDL_Texture* Entity::getTexture()
{
    return texture;
}

int& Entity::getWidth()
{
    return size.w;
}

int& Entity::getHeight()
{
    return size.h;
}

std::pair<SDL_Rect, Vector2f>& Entity::getCurrentFrame(int index)
{
    return current_frame[index];
}

int Entity::getCurrentFrameLength()
{
    return current_frame.size();
}

void Entity::addTileToCurrentFrame(int tile_x, int tile_y, int x_offset, int y_offset)
{
    SDL_Rect tile;
    tile.x = tile_x;
    tile.y = tile_y;
    tile.w = tile_size.w;
    tile.h = tile_size.h;

    Vector2f pos_offset;
    pos_offset.x = x_offset;
    pos_offset.y = y_offset;

    current_frame.push_back(std::make_pair(tile, pos_offset));
}
