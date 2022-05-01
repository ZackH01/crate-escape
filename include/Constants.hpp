#pragma once

namespace constants
{
    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;
    const int SCREEN_CENTRE_X = SCREEN_WIDTH/2;
    const int GAME_LEFT_BORDER = 480;
    const int GAME_RIGHT_BORDER = 960;
    const int GAME_BOTTOM_BORDER = 688;
    const int GAME_TOP_BORDER = 32;
    const int GAME_WIDTH = GAME_RIGHT_BORDER - GAME_LEFT_BORDER;
    const int GAME_HEIGHT = GAME_BOTTOM_BORDER - GAME_TOP_BORDER;
    const int GAME_CENTRE_X = GAME_LEFT_BORDER + 0.5*GAME_WIDTH;
    const int GAME_CENTRE_Y = GAME_TOP_BORDER + 0.5*GAME_HEIGHT;
    const int GAME_TEXT_X_POS = 220;
    const int GAME_TEXT_Y_POS = 120;
    const int TILE_SIZE = 32;
}

enum GameState
{
    GAME_RUNNING,
    GAME_PAUSED,
    START_SCREEN,
    LEVEL_CLEAR,
    GAME_OVER
};
