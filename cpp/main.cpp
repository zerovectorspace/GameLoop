#include "h/SDLWindow.h"
#include "h/GameLoop.h"

class myGameLoop: public GameLoop{
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
        // I can do whatever I want here. 
        return *this;
    }
    virtual GameLoop& updatePositions(){
        // (Optional though recommended)
        // I should update the position of my actors here.

        // I can use this->deltaTime to update my actor positions
        return *this;
    }
    virtual GameLoop& interpolate(){
        // (Optional)
        // I should interpolate the animations of my actors here.

        // I can use this->interpolate and this->deltaTime to animate my actors
        return *this;
    }
    virtual GameLoop& draw(){
        // I should draw everything here.
        // I will definitely put things here or I will see nothing in my window.
        return *this;
    }
};

int main (int argc, char* argv[])
{
    SDLWindow win("My Game", 800, 600, SDL_WINDOW_SHOWN);
    myGameLoop myGame;
    return 0;
}   