#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Crate.hpp"
#include "Maths.hpp"

Crate::Crate(SDL_Texture* crate_texture, int tile_width, int tile_height, int crate_width, int crate_height)
:Entity(Vector2f(), crate_texture, tile_width, tile_height)
{
    position.x = 528;
    position.y = 560;

    //Validate crate width and height (Min = 2x2, max = 4x4)
    if(crate_width < 2 || crate_width > 4 || crate_height < 2 || crate_width > 4)
    {
        std::cout << "Error: crate width and height should be between 2 and 4 (inclusive)!" << std::endl;
        return;
    }

    //Create crate texture from individual tiles
    int tile_offset_x;
    int tile_offset_y;

    for(int i = 0; i < crate_width; i++)
    {
        //Left tile
        if(i == 0)
        {
            tile_offset_x = 0;
        }
        //Right tile
        else if(i == crate_width-1)
        {
            tile_offset_x = 2;
        }
        //Middle tile
        else
        {
            tile_offset_x = 1;
        }

        for(int j = 0; j < crate_height; j++)
        {
            //Move on as this tile is already in the texture
            if(i == 0 && j == 0)
            {
                continue;
            }

            //Top tile
            if(j == 0)
            {
                tile_offset_y = 0;
            }
            //Bottom tile
            else if(j == crate_height-1)
            {
                tile_offset_y = 2;
            }
            //Middle tile
            else
            {
                tile_offset_y = 1;
            }

            addTileToCurrentFrame(tile_offset_x*tile_width, tile_offset_y*tile_height, i*tile_width, j*tile_height);
        }
    }
}
