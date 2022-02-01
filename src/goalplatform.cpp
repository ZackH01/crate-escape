#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Maths.hpp"
#include "GoalPlatform.hpp"

GoalPlatform::GoalPlatform(SDL_Texture* platform_texture, int y_pos)
:Entity(platform_texture, Vector2f(400, y_pos), 480, 8)
{
    setHitbox(0, 0, 480, 1);
}
