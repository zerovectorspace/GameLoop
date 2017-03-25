#include "../h/SDLWindow.h"
#include "../h/GameLoop.h"
#include "../h/Events.h"
#include "../h/Rectangle.h"
#include "../h/Settings.h"

//#include <GL/glew.h>
//#include <glm/glm.hpp>
//#include <glm/ext.hpp>

class myGameLoop :
    public GameLoop
{
    using GameLoop::GameLoop;

private:
    Events event_map;

    Rectangle green;
    Rectangle blue;

public:
    void init() override
    {
        green = Rectangle{
            41, 224, 51,
            0, 0,
            50, 50,
            300, 300};

        blue = Rectangle{
            50, 134, 255,
            100, 100,
            50, 50,
            300, 300};
    }

    void second_tick() override
    {
        console_output();
    }

    void inputs(SDL_Event& events) override
    {
        event_map.run(events);

        if (events.type == SDL_KEYDOWN &&
                events.key.keysym.sym == SDLK_SPACE)
            toggle_pause();
    }

    void update_positions(const float& delta) override
    {
        green.update_position(delta);
        blue.update_position(delta);
    }

    void collisions() override
    {
        green.collisions();
        blue.collisions();

    }

    void interpolate(const float& delta, const float& interpolation) override
    {
        green.interpolate(delta, interpolation);
        //blue.interpolate(delta, interpolation);
    }

    void draw() override
    {
        SDL_SetRenderDrawColor(rend, 0,0,0,0);
        SDL_RenderClear(rend);

        green.draw(rend);
        blue.draw(rend);

        SDL_RenderPresent(rend);
    }
};

int main (int argc, char* argv[])
{
    Settings opts;
    opts.build();

    SDLWindow win(
        "My Game",
        std::stoi(opts.get("window_width")),
        std::stoi(opts.get("window_height")),
        SDL_WINDOW_SHOWN,
        SDL_RENDERER_ACCELERATED);

    //glewExperimental = GL_TRUE;
    //glewInit();

    myGameLoop myGame(
            std::stoi(opts.get("target_fps")),
            static_cast<GameLoop::INTERPOLATIONS>(
                std::stoi(opts.get("frame_partitions")))
    );

    myGame.start(win);

    return 0;
}
