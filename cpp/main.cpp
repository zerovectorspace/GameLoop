#include "../h/SDLWindow.h"
#include "../h/GameLoop.h"
#include "../h/Events.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class myGameLoop :
    public GameLoop
{
    using GameLoop::GameLoop;
private:

    Events event_map;

public:
    void init() override
    {

    }

    void second_tick() override
    {
        console_output();
    }

    void inputs(SDL_Event& events) override
    {
        event_map.run(events);
    }

    void update_positions() override
    {

    }

    void collisions() override
    {

    }

    void interpolate(float delta) override
    {

    }

    void draw() override
    {
        SDL_GL_SwapWindow(win);
    }
};

int main (int argc, char* argv[])
{
    SDLWindow win("My Game", 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    glewExperimental = GL_TRUE;
    glewInit();

    myGameLoop myGame(30, myGameLoop::INTERPOLATIONS::ONE);

    myGame.start(win);

    return 0;
}
