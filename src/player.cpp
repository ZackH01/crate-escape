#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "Entity.hpp"
#include "Maths.hpp"
#include "Player.hpp"

Player::Player(Vector2f position, SDL_Texture* player_texture, int texture_width, int texture_height)
:Entity(position, player_texture, texture_width, texture_height)
{
    direction = "none";
}

void Player::move()
{
    float max_vel = 7.5f;
    float acceleration = 0.5f;

    if(direction == "none")
    {
        //Slow down to a stop
        if(velocity.x > 1.25*acceleration)
        {
            velocity.x -= 1.25*acceleration;
        }
        else if(velocity.x < -1.25*acceleration)
        {
            velocity.x += 1.25*acceleration;
        }
        else
        {
            velocity.x = 0;
        }
    }
    else if(direction == "right")
    {
        //Move right
        if(velocity.x < max_vel)
        {
            velocity.x += acceleration;
        }
    }
    else if(direction == "left")
    {
        //Move left
        if(velocity.x > -max_vel)
        {
            velocity.x -= acceleration;
        }
    }
    else
    {
        std::cout << "Unknown direction: " << direction << std::endl;
    }
    changePosition(velocity);
}

void Player::setDirection(std::string dir)
{
    direction = dir;
}
