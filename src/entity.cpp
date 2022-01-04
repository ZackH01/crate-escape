#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Entity.hpp"
#include "Maths.hpp"

Entity::Entity(Vector2f pos, SDL_Texture* entity_texture, int texture_width, int texture_height)
:position(pos), texture(entity_texture), current_frame(0)
{
    //Adds first tile in the texture to the initial frame
    SDL_Rect default_tile_src;
    default_tile_src.x = 0;
    default_tile_src.y = 0;
    default_tile_src.w = texture_width;
    default_tile_src.h = texture_height;

    Vector2f default_tile_dst_offset;
    default_tile_dst_offset.x = 0;
    default_tile_dst_offset.y = 0;

    current_frame.push_back(std::make_pair(default_tile_src, default_tile_dst_offset));
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
    tile.w = getCurrentFrame().first.w;
    tile.h = getCurrentFrame().first.h;

    Vector2f pos_offset;
    pos_offset.x = x_offset;
    pos_offset.y = y_offset;

    current_frame.push_back(std::make_pair(tile, pos_offset));
}
