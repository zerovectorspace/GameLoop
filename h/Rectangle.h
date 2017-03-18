#ifndef __RECTANGLE__
#define __RECTANGLE__

#include "SDL2/SDL.h"
#include <array>

class Rectangle
{
public:
    SDL_Rect rect{0, 0, 50, 50};
    std::array<int, 4> color;

    int prev_x = 0;
    int prev_y = 0;

    float vel_x = 0.0f;
    float vel_y = 0.0f;

    Rectangle() {}
    Rectangle(
            const int r,
            const int g,
            const int b,
            const int init_x,
            const int init_y,
            const int init_width,
            const int init_height,
            const float init_vel_x,
            const float init_vel_y
    )
        :
            prev_x{init_x},
            prev_y{init_y},
            vel_x{init_vel_x},
            vel_y{init_vel_y}
    {
        color[0] = r;
        color[1] = g;
        color[2] = b;
        rect = {init_x, init_y, int(init_width), int(init_height)};
    }

    ~Rectangle() {}

    void collisions()
    {
        if (rect.x < 0)
            vel_x *= -1;
        if (rect.x > 800 - rect.w)
            vel_x *= -1;
        if (rect.y < 0)
            vel_y *= -1;
        if (rect.y > 600 - rect.h)
            vel_y *= -1;
    }

    void update_position(const float& delta)
    {
        rect.x = prev_x + vel_x * delta;
        rect.y = prev_y + vel_y * delta;

        prev_x = rect.x;
        prev_y = rect.y;
    }

    void interpolate(const float& delta, const float& interpolation)
    {
        rect.x = prev_x + vel_x * delta * interpolation;
        rect.y = prev_y + vel_y * delta * interpolation;
    }

    void draw(SDL_Renderer* rend)
    {
        SDL_SetRenderDrawColor(rend, color[0], color[1], color[2], color[3]);
        SDL_RenderFillRect(rend, &rect);
    }
};

#endif
