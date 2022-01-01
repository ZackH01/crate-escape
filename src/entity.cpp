#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.hpp"
#include "Maths.hpp"

Entity::Entity(Vector2f pos, SDL_Texture* entity_texture, int texture_width, int texture_height)
:position(pos), texture(entity_texture)
{
    current_frame.x = 0;
    current_frame.y = 0;
    current_frame.w = texture_width;
    current_frame.h = texture_height;
}

Vector2f& Entity::getPosition()
{
    return position;
}

SDL_Texture* Entity::getTexture()
{
    return texture;
}

SDL_Rect Entity::getCurrentFrame()
{
    return current_frame;
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
