#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "RenderWindow.hpp"
#include "Player.hpp"
#include "Crate.hpp"
#include "GoalPlatform.hpp"

class Game
{
    public:
        Game(RenderWindow* w);
        void gameLoop(SDL_Event e);

    private:
        void addCrate();
        void resetGame();
        void renderGame();
        void loadGameTextures();
        RenderWindow* window;
        SDL_Texture* background;
        SDL_Texture* top_cover;
        SDL_Texture* player_texture;
        SDL_Texture* crate_texture;
        SDL_Texture* platform_texture;
        Player player;
        GoalPlatform goal;
        std::vector<Crate> crates;
        int time;
        int level;
        int crate_frequency;
        float crate_speed;
};
