#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.hpp"
#include "Maths.hpp"

Entity::Entity(Vector2f position, SDL_Texture* entity_texture, int texture_width, int texture_height)
:pos(position), texture(entity_texture)
{
    current_frame.x = 0;
    current_frame.y = 0;
    current_frame.w = texture_width;
    current_frame.h = texture_height;
}

Vector2f& Entity::getPosition()
{
    return pos;
}

SDL_Texture* Entity::getTexture()
{
    return texture;
}

SDL_Rect Entity::getCurrentFrame()
{
    return current_frame;
}
