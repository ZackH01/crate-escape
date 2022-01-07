#pragma once

struct Vector2f
{
    Vector2f();
    Vector2f(float x_pos, float y_pos);
    float x, y;
};

struct EntDim
{
    EntDim();
    int w, h;
};

struct HitboxRect
{
    //Positions are offset from the entity's position
    HitboxRect();
    float x1, y1, x2, y2;
};
