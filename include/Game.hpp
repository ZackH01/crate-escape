#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "RenderWindow.hpp"
#include "Text.hpp"
#include "Button.hpp"
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
        void updateUI();
        void renderGame();
        void loadGameTextures();
        RenderWindow* window;
        SDL_Texture* background;
        SDL_Texture* paused_shader;
        SDL_Texture* top_cover;
        SDL_Texture* player_texture;
        SDL_Texture* crate_texture;
        SDL_Texture* platform_texture;
        SDL_Texture* button_texture;
        TTF_Font* text_font;
        Player player;
        GoalPlatform goal;
        std::vector<Crate> crates;
        Text level_text;
        Text score_text;
        Text paused_text;
        Button continue_button;
        bool paused;
        int time;
        int level;
        int score;
        int crate_frequency;
        float crate_speed;
};
