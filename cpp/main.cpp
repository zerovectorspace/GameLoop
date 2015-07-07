#include "h/SDLWindow.h"
#include "h/GameLoop.h"

// #include <GL/glew.h>
// #include <glm/glm.hpp>
// #include <glm/ext.hpp>

class myGameLoop: public GameLoop{
    // I must implicitly inherit constructors from GameLoop
    // If I don't, I can't control updatesPerSecond or Interpolation
        // Only default constructor will be allowed
    using GameLoop::GameLoop;
public:
    myGameLoop& init() override {
        // (Optional)
        // I can do anything here before the main loop starts
        return *this;
    }
    myGameLoop& secondTimer() override {
    	// (Optional)
    	// This function is called every second
    	this->consoleOutput();
    	return *this;
    }
    myGameLoop& inputs() override {
        // (Optional though recommended)
        // I can do whatever I want here. Inputs work well here
            // as it is still the beginning of the loop
        // this->e is an SDL_Event
        // This function is called as fast as your processor can work
        // This function is called for every single event until the
            // event queue is empty
        switch (this->e.type) {
            case SDL_KEYDOWN: {
                if (!this->e.key.repeat)
                    std::cout << "Key Code: " << this->e.key.keysym.scancode << "\t" <<
                        "Name: " << SDL_GetScancodeName(this->e.key.keysym.scancode) << "\n";

                break;
            }
        }
        return *this;
    }
    myGameLoop& updatePositions() override {
        // (Optional though recommended)
        // I should update the position of my actors here.
        // This is only called at updatesPerSecond (default is 60)

        // I should use this->deltaTime to update my actor positions
        return *this;
    }
    myGameLoop& collisions() override {
        // (Optional though recommended)
        // I should check for any collisions here
        // This is only called at updatesPerSecond (default is 60)
        // This is called directly after this->updatePositions()

        return *this;
    }
    myGameLoop& interpolate() override {
        // (Optional)
        // I should interpolate the animations of my actors here.

        // I should use this->interpolation and this->deltaTime to animate my actors
        return *this;
    }
    myGameLoop& draw() override {
        // I should draw everything here.
        // I will definitely put things here or I will see nothing in my window.
        // If I'm using opengl I need to swap the buffers or I won't see anything
        SDL_GL_SwapWindow(this->win);
        return *this;
    }
};

int main (int argc, char* argv[])
{
    // I can define the window title, width, height, and SDL_WindowFlags
    // in the SDLWindow constructor
    SDLWindow win("My Game", 800, 600, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);

    // Here is a good place to intialize GLEW; just after the context has been
	// attached to the window
    // glewExperimental = GL_TRUE;
    // glewInit();

    myGameLoop myGame(30, "medium");

    // Start off the mainloop.
        // We can't start it automatically in the constructor
        // because the functions won't be overridden. 
    // I send it the SDLWindow so i can manipulate the window
    // in my derived myGameLoop class
    myGame.start(win);
    return 0;
}   