#include "Maths.hpp"

Vector2f::Vector2f()
:x(0.0f), y(0.0f)
{}

Vector2f::Vector2f(float x_pos, float y_pos)
:x(x_pos), y(y_pos)
{}

EntDim::EntDim()
:w(0), h(0)
{}

HitboxRect::HitboxRect()
:x1(0), y1(0), x2(0), y2(0)
{}
