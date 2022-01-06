#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <iostream>
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

    //Default hitbox size, hitbox coords are relative to the entity's position
    hitbox.x1 = 0;
    hitbox.y1 = 0;
    hitbox.x2 = e_width;
    hitbox.y2 = e_height;
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

    //Default hitbox size, hitbox coords are relative to the entity's position
    hitbox.x1 = 0;
    hitbox.y1 = 0;
    hitbox.x2 = e_width;
    hitbox.y2 = e_height;
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

HitboxRect& Entity::getHitbox()
{
    return hitbox;
}

void Entity::setHitbox(float x_offset, float y_offset, float width, float height)
{
    hitbox.x1 = x_offset;
    hitbox.y1 = y_offset;
    hitbox.x2 = x_offset + width;
    hitbox.y2 = y_offset + height;
}

bool Entity::checkCollision(Entity& entity)
{
    //Your hitbox
    HitboxRect yhb = hitbox;
    yhb.x1 += position.x;
    yhb.y1 += position.y;
    yhb.x2 += position.x;
    yhb.y2 += position.y;

    //Hitbox of the entity you are checking collision with
    HitboxRect ehb = entity.getHitbox();
    Vector2f epos = entity.getPosition();
    ehb.x1 += epos.x;
    ehb.y1 += epos.y;
    ehb.x2 += epos.x;
    ehb.y2 += epos.y;

    //Check if the hitboxes overlap
    if(yhb.x1 < ehb.x2 && yhb.x2 > ehb.x1 && yhb.y1 < ehb.y2 && yhb.y2 > ehb.y1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
