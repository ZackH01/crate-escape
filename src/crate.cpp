#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Crate.hpp"
#include "Maths.hpp"

Crate::Crate(SDL_Texture* crate_texture, int tile_width, int tile_height)
:Entity(Vector2f(), crate_texture, tile_width, tile_height)
{
	position.x = 500;
	position.y = 300;
}
