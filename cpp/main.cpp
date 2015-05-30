#include "h/SDLWindow.h"
#include "h/GameLoop.h"

class myGameLoop: public GameLoop{
    // I must implicitly inherit constructors from GameLoop
    // If I don't, I can't control updatesPerSecond or Interpolation
        // Only default constructor will be allowed
    using GameLoop::GameLoop;
public:
    virtual GameLoop& init(){
        // (Optional)
        // I can do anything here before the main loop starts
        return *this;
    }
    virtual GameLoop& consoleOutput(){
        // (Optional)
        // I can do whatever I want here at the beginning of the loop
        return *this;
    }
    virtual GameLoop& inputs(){
        // (Optional though recommended)
        // I can do whatever I want here. Inputs work well here
            // as it is still the beginning of the loop
        // this->e is an SDL_Event that holds all the inputs
        // This function is called as fast as your processor can work 
        return *this;
    }
    virtual GameLoop& updatePositions(){
        // (Optional though recommended)
        // I should update the position of my actors here.
        // This is only called at updatesPerSecond (default is 60)

        // I should use this->deltaTime to update my actor positions
        return *this;
    }
    virtual GameLoop& interpolate(){
        // (Optional)
        // I should interpolate the animations of my actors here.

        // I should use this->interpolation and this->deltaTime to animate my actors
        return *this;
    }
    virtual GameLoop& draw(){
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
    myGameLoop myGame(30, "slow");

    // Start off the mainloop.
        // We can't start it automatically in the constructor
        // because the functions won't be overridden. 
    // I send it the SDLWindow so i can manipulate the window
    // in my derived myGameLoop class
    myGame.start(win);
    return 0;
}   