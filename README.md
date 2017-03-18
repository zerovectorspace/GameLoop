# Easy Game Loop

These are headers to start up a window with SDL2 and start a game loop. You can use SDL2 to start up your window then deal with input and looping on your own or start up a game loop for a console loop.

## Prerequisites

* SDL2
* CMake
* C++14

## Installation

* `git clone` this repository.
* `cmake /path/to/repository`
* `cmake && ./GameLoop`

## Features

* Build your application from the ground up
* Selectable FPS
* Interpolation between frames
* Events class handles events without switch statements or long if / else if chains

## Notes

When first running the engine you will see a blue and green square floating around the window. When constructing `myGameLoop`, the target FPS is set to 15 FPS while the interpolation is set to four draws per frame. This means the positions and collisions are calculated 15 times per second while it draws each object 60 times per second. Since the blue square isn't interpolated, the animation is not smooth.

If you want to use OpenGL, `or` the SDL_Window options with `SDL_WINDOW_OPENGL`.
If you want to Vsync the renderer, `or` the SDL_Renderer options with `SDL_RENDERER_PRESENTVSYNC`. This will limit the interpolation draws to 60 FPS.
