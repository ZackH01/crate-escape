#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Maths.hpp"
#include "Crate.hpp"

//Representation of where crates are currently placed - game size is 15x18 tiles
int Crate::crate_map[18][15] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

Crate::Crate(SDL_Texture* crate_texture)
:Entity(crate_texture, Vector2f(), 0, 0, 32, 32), falling(true), fall_velocity(0)
{
    //Find all possible placements and sizes (from width 1-4) such that there are no overhangs
    std::vector<std::pair<int, int>> valid_placements; //std::vector of pairs (x_pos, width)

    for(int w = 1; w <= 4; w++)
    {
        for(int x = 0; x <= 15-w; x++)
        {
            //A crate of width 1 can always be placed so skip checking these crates
            bool valid = true;
            if(w > 1)
            {
                //Find where the leftmost tile of the crate would land
                int y = -1;
                while(crate_map[y+1][x] == 0 && y < 17)
                {
                    y++;
                }

                //Then check that all remaining tiles to the right don't collide with a crate and don't leave any overhangs
                for(int i = 1; i < w; i++)
                {
                    if(crate_map[y][x+i] == 1)
                    {
                        valid = false;
                    }
                    if(y < 17 && crate_map[y+1][x+i] == 0)
                    {
                        valid = false;
                    }
                }
            }

            if(valid)
            {
                valid_placements.push_back(std::make_pair(x, w));
            }
        }
    }

    //Pick a random valid x_pos and width
    std::pair<int, int> selection = valid_placements[std::rand() % valid_placements.size()];
    int x_pos = selection.first;
    int crate_width = selection.second;

    //Frequency of the crate heights
    const int height_freq[10] = {1, 2, 2, 2, 2, 3, 3, 3, 3, 4};

    //Set crate dimensions
    int crate_height = height_freq[std::rand()%10];
    setSize(crate_width*32, crate_height*32);
    setHitbox(0, 0, crate_width*32, crate_height*32);

    //Set start position
    position.x = x_pos*32 + 400;
    position.y = 112-getHeight();

    //Update map
    bool placed = false;
    int depth = 0;

    while(!placed && depth < 18)
    {
        for(int i = x_pos; i < crate_width+x_pos; i++)
        {
            if(crate_map[depth+1][i] == 1 || depth == 17)
            {
                //Place crate
                for(int x = x_pos; x < crate_width+x_pos; x++)
                {
                    for(int y = depth; y > depth-crate_height; y--)
                    {
                        if(y >= 0)
                        {
                            crate_map[y][x] = 1;
                        }
                    }
                }
                placed = true;
                break;
            }
        }
        depth++;
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

void Crate::resetCrateMap()
{
    for(int i = 0; i < 18; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            crate_map[i][j] = 0;
        }
    }
}

void Crate::printCrateMap()
{
    for(int i = 0; i < 18; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            std::cout << crate_map[i][j] << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
