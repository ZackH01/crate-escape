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
}

void Player::move(std::string direction)
{
    if(direction == "right")
    {
        changePosition(Vector2f(2, 0));
    }
    else if(direction == "left")
    {
        changePosition(Vector2f(-2, 0));
    }
    else
    {
        std::cout << "Unknown direction: " << direction << std::endl;
    }
}