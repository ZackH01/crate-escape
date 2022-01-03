#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Crate.hpp"
#include "Maths.hpp"

Crate::Crate(SDL_Texture* crate_texture, int tile_width, int tile_height)
:Entity(Vector2f(), crate_texture, tile_width, tile_height)
{
	//Initial position, y-value will be randomised
	position.x = 528;
	position.y = 560;
}
