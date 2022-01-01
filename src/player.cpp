#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "Entity.hpp"
#include "Maths.hpp"
#include "Player.hpp"

Player::Player(Vector2f pos, SDL_Texture* player_texture, int texture_width, int texture_height)
:Entity(pos, player_texture, texture_width, texture_height)
{
    direction = "none";
}

void Player::move()
{
    //Horizontal movement
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

    //Vertical movement
    float gravity = 1.0f;
    velocity.y += gravity;

    //Jump
    if(jump_input)
    {
        velocity.y -= 20;
        jump_input = false;
        can_jump = false;
    }

    changePosition(velocity);

    //Check collision with the floor
    if(position.y > 632)
    {
        position.y = 632;
        velocity.y = 0;
        can_jump = true;
    }
}

void Player::jump()
{
    if(can_jump)
    {
        jump_input = true;
    }
}

void Player::setDirection(std::string dir)
{
    direction = dir;
}
