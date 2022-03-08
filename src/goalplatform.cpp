#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Constants.hpp"
#include "Maths.hpp"
#include "GoalPlatform.hpp"

using namespace constants;

GoalPlatform::GoalPlatform(SDL_Texture* platform_texture, int y_pos)
:Entity(platform_texture, Vector2f(GAME_LEFT_BORDER, y_pos), GAME_WIDTH, 8)
{
    setHitbox(0, 0, GAME_WIDTH, 1);
}
