#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "Constants.hpp"
#include "RenderWindow.hpp"
#include "Text.hpp"
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
        void updateGameUI();
        void renderGame();
        void loadGameTextures();
        GameState state;
        RenderWindow* window;
        SDL_Texture* game_background;
        SDL_Texture* background;
        SDL_Texture* paused_shader;
        SDL_Texture* player_texture;
        SDL_Texture* crate_texture;
        SDL_Texture* platform_texture;
        TTF_Font* font_18;
        TTF_Font* font_36;
        TTF_Font* font_72;
        Player player;
        GoalPlatform goal;
        std::vector<Crate> crates;
        Text title_text;
        Text continue_text;
        Text level_text;
        Text score_text;
        Text paused_text;
        Text level_clear_text;
        Text clear_bonus_text;
        Text time_bonus_text;
        Text game_over_text;
        int time;
        int level;
        int score;
        int crate_frequency;
        float crate_speed;
};
