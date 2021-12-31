#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "Entity.hpp"
#include "Maths.hpp"
#include "Player.hpp"

Player::Player(Vector2f position, SDL_Texture* player_texture, int texture_width, int texture_height)
:Entity{position, player_texture, texture_width, texture_height}
{
    direction = "none";
}

void Player::move()
{
    if(direction == "none")
    {
        return;
    }
    else if(direction == "right")
    {
        //Move right
        changePosition(Vector2f(2, 0));
    }
    else if(direction == "left")
    {
        //Move left
        changePosition(Vector2f(-2, 0));
    }
    else
    {
        std::cout << "Unknown direction: " << direction << std::endl;
    }
}

std::string Player::getDirection()
{
    return direction;
}

void Player::setDirection(std::string dir)
{
    direction = dir;
}
