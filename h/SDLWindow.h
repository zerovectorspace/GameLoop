#ifndef _SDL_WINDOW_
#define _SDL_WINDOW_

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <thread>

class SDLWindow{
private:
    SDL_Window* win = NULL;
    SDL_Renderer* rend = NULL;
    SDL_Event e;
    bool isRunning = true;
    std::thread quitEventThread;

    SDLWindow& initSDL(){
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
          std::cout << "could not initialize SDL2 \n" << SDL_GetError() << "\n";
        }
        return *this;
    }
    SDLWindow& initWindow(const std::string& name="Game Loop", 
        const uint& width=800, 
        const uint& height=600, 
        const uint& opts=SDL_WINDOW_SHOWN)
    {
        this->win = SDL_CreateWindow((const char*)name.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            opts);

        if (this->win == NULL)
        {
            std::cout << "Could not create Window\n" << SDL_GetError() << "\n";
        }
        return *this;
    }
    SDLWindow& initRenderer(){
        this->rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED||SDL_RENDERER_PRESENTVSYNC);

        if (this->rend == NULL)
        {
            std::cout << "Could not create Renderer\n" << SDL_GetError() << "\n";
        }
        return *this;
    }

public:
    SDLWindow(){
        this->initSDL()
            .initWindow()
            .initRenderer();
    }
    SDLWindow(std::string& n){
        this->initSDL()
            .initWindow(n)
            .initRenderer();
    }
    SDLWindow(const std::string& n, const uint& w, const uint& h){
        this->initSDL()
            .initWindow(n, w, h)
            .initRenderer();
    }
    SDLWindow(const std::string& n, const uint& w, const uint& h, const uint& o){
        this->initSDL()
            .initWindow(n, w, h, o)
            .initRenderer();
    }
    ~SDLWindow(){
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
    }
};

#endif