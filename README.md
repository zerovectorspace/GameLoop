# Easy Game Loop

These are headers to start up a window with SDL2, start a game loop, or both. You can use SDL2 to start up your window then deal with input and looping on your own or start up a game loop for a console loop.

## Prerequisites

* SDL2
* Bazel (There is a Bazel BUILD file included. It's not needed as you can create your own makefile or use cmake)
* C++11

## Installation

`git clone` this repository.

```C++
#include "h/SDLWindow.h"
#include "h/GameLoop.h"
```

## SDLWindow Constructors

```C++
// Make an 800x600 window with a name of "Game Loop"
SDLWindow myWindow;

// Make an 800x600 window with a name of "My Totally Awesome Game"
SDLWindow myWindow("My Totally Awesome Game");

//Make a 640x480 window with a name of "My Totally Awesome Game"
SDLWindow myWindow ("My Totally Awesome Game", 640, 480);

//Make a 640x480 window with a name of "My Totally Awesome Game" with an OpenGL Context and no border (It's your responsibility to include opengl and compile/link against it)
SDLWindow myWindow ("My Totally Awesome Game", 640, 480, SDL_WINDOW_OPENGL|SDL_WINDOW_BORDERLESS);
```

If the SDL_WINDOW_OPENGL flag is included in the window options an [SDL_GLContext](https://wiki.libsdl.org/SDL_GL_CreateContext) is created for you

## GameLoop Constructors

```C++
// Create a game loop at 60 updatesPerSecond
GameLoop myGame;

// Create a game loop at 30 updatesPerSecond
GameLoop myGame(30);

// Create a game loop at 30 updatesPerSecond that interpolates at 0% and 50%
    // Second argument values can be: "slow" (0%, 50%), "medium" (0%, 30%, 60%, 90%), "fast" (As fast as possible)
GameLoop myGame(30, "slow");
```

## GameLoop Overrides

```C++
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
        return *this;
    }
};
```
