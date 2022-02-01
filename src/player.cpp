#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include "Maths.hpp"
#include "Player.hpp"
#include "Crate.hpp"

Player::Player(SDL_Texture* player_texture)
:Entity(player_texture, Vector2f(624, 720), 32, 32)
{
    direction = "none";
    can_jump = false;
    jump_input = false;
    can_land_on_platform = false;
    game_over = false;
}

void Player::move(std::vector<Crate>& crate_vect, GoalPlatform& goal)
{
    //Vertical movement
    float gravity;
    float max_y_vel = 15;

    if(velocity.y < 0)
    {
        gravity = 0.8f;
    }
    else
    {
        //Stronger gravity when falling
        gravity = 1.0f;
    }
    velocity.y += gravity;

    if(velocity.y > max_y_vel)
    {
        velocity.y = max_y_vel;
    }

    //Jump
    if(jump_input)
    {
        velocity.y = -15.0f;
        jump_input = false;
        can_jump = false;
    }

    //Update y position
    changePosition(Vector2f(0, velocity.y));

    //Check collision with the floor
    if(position.y > 688-getHeight())
    {
        position.y = 688-getHeight();
        velocity.y = 0;
        can_jump = true;
    }
    
    //Check collision with the goal platform, if the player lands on it then the level is cleared
    HitboxRect phb = getHitbox();

    if(checkCollision(goal) && can_land_on_platform)
    {
        game_over = true;
        position.y = goal.getPosition().y-getHeight();
        velocity.y = 0;
    }
    else if (phb.y2 < goal.getPosition().y)
    {
        can_land_on_platform = true;
    }

    //Check collision with crates
    HitboxRect chb;

    for(Crate& crate: crate_vect)
    {
        if(checkCollision(crate))
        {
            chb = crate.getHitbox();

            //Touched top of crate
            if(phb.y2 > chb.y1 && phb.y1 < chb.y1)
            {
                position.y = chb.y1-getHeight();
                velocity.y = crate.getFallVelocity();
                current_crate_velocity = crate.getFallVelocity();
                can_jump = true;
            }
            //Touched bottom of crate
            else if(phb.y1 < chb.y2 && phb.y2 > chb.y2)
            {
                position.y = chb.y2+crate.getFallVelocity();
                velocity.y = crate.getFallVelocity();

                //Kill player if they hit the bottom of a falling crate
                if(crate.getFallVelocity())
                {
                    game_over = true;
                }
            }
        }
    }

    //Horizontal movement
    float max_x_vel = 5.0f;
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
        velocity.x += acceleration;
        if(velocity.x > max_x_vel)
        {
            velocity.x = max_x_vel;
        }
    }
    else if(direction == "left")
    {
        //Move left
        velocity.x -= acceleration;
        if(velocity.x < -max_x_vel)
        {
            velocity.x = -max_x_vel;
        }
    }
    else
    {
        std::cout << "Unknown direction: " << direction << std::endl;
    }

    //Update x position
    changePosition(Vector2f(velocity.x, 0));

    //Check collision with left and right borders
    if(position.x < 400)
    {
        position.x = 400;
        velocity.x = 0;
    }
    if(position.x > 880-getWidth())
    {
        position.x = 880-getWidth();
        velocity.x = 0;
    }

    //Check collision with crates
    for(Crate& crate: crate_vect)
    {
        if(checkCollision(crate))
        {
            //Your hitbox
            phb = getHitbox();

            //Get position of crate's hitbox
            chb = crate.getHitbox();

            //Touched left side
            if(phb.x2 > chb.x1 && phb.x1 < chb.x1)
            {
                position.x = chb.x1-getWidth();
                velocity.x = 0;
            }
            //Touched right side
            else if(phb.x1 < chb.x2 && phb.x2 > chb.x2)
            {
                position.x = chb.x2;
                velocity.x = 0;
            }
        }
    }
}

void Player::jump()
{
    if(can_jump && (velocity.y == 0 || velocity.y == current_crate_velocity))
    {
        jump_input = true;
    }
}

void Player::setDirection(std::string dir)
{
    direction = dir;
}

bool& Player::isGameOver()
{
    return game_over;
}
