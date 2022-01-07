#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Maths.hpp"
#include "Crate.hpp"

Crate::Crate(SDL_Texture* crate_texture, int crate_width, int crate_height)
:Entity(crate_texture, Vector2f(), crate_width*32, crate_height*32, 32, 32)
{
    while(position.x < 400 || position.x > 880-getWidth())
    {
        position.x = (std::rand()%15)*32 + 400;
    }
    position.y = -getHeight();

    //Validate crate width and height
    if(crate_width < 1 || crate_width < 1)
    {
        std::cout << "Error: crate width and height must be 1 or greater!" << std::endl;
        return;
    }

    //Create crate texture from individual tiles
    int tile_offset_x;
    int tile_offset_y;

    for(int i = 0; i < crate_width; i++)
    {
        //Tile for width of 1
        if(crate_width == 1)
        {
            tile_offset_x = 3;
        }
        //Left tile
        else if(i == 0)
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
            //Tile for height of 1
            if(crate_height == 1)
            {
                tile_offset_y = 3;
            }
            //Top tile
            else if(j == 0)
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

            addTileToCurrentFrame(tile_offset_x*32, tile_offset_y*32, i*32, j*32);
        }
    }
}

void Crate::move(std::vector<Crate>& crate_vect)
{
    if(falling)
    {
        //Move down
        float gravity = 0.25f;
        float max_vel = 4.0f;

        if(fall_velocity < max_vel)
        {
            fall_velocity += gravity;
        }

        changePosition(Vector2f(0, fall_velocity));

        //Check collision with the floor
        if(position.y > 688-getHeight())
        {
            position.y = 688-getHeight();
            falling = false;
            fall_velocity = 0;
        }

        //Check collision with crates (not including itself)
        for(Crate& crate: crate_vect)
        {
            if(position.x == crate.getPosition().x && position.y == crate.getPosition().y)
            {
                //Skip, don't check collision with yourself
                continue;
            }
            else if(checkCollision(crate))
            {
                position.y = crate.getPosition().y-getHeight();
                falling = false;
                fall_velocity = 0;
            }
        }
    }
}

float& Crate::getFallVelocity()
{
    return fall_velocity;
}
