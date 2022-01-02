#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Entity.hpp"
#include "Maths.hpp"

Entity::Entity(Vector2f pos, SDL_Texture* entity_texture, int texture_width, int texture_height)
:position(pos), texture(entity_texture)
{
    SDL_Rect default_frame;
    default_frame.x = 0;
    default_frame.y = 0;
    default_frame.w = texture_width;
    default_frame.h = texture_height;

    current_frame.push_back(default_frame);
}

Vector2f& Entity::getPosition()
{
    return position;
}

SDL_Texture* Entity::getTexture()
{
    return texture;
}

SDL_Rect Entity::getCurrentFrame(int index)
{
    return current_frame[index];
}

int Entity::getCurrentFrameLength()
{
    return current_frame.size();
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
