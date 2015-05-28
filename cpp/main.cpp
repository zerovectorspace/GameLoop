#include "h/SDLWindow.h"
#include "h/GameLoop.h"

int main (int argc, char* argv[])
{
    SDLWindow win("My Game", 800, 600, SDL_WINDOW_SHOWN);
    GameLoop myGame;
    return 0;
}   