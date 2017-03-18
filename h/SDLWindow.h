#ifndef _SDL_WINDOW_
#define _SDL_WINDOW_

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

class SDLWindow{
public:
    SDL_Window* win = nullptr;

private:
    SDL_Renderer* rend = nullptr;
    SDL_GLContext glContext = nullptr;

public:
    SDLWindow(const std::string& n = "Game Loop",
            const uint& w = 800,
            const uint& h = 600,
            const int& o = SDL_WINDOW_SHOWN)
    {
        if (initSDL())
            initWindow(n, w, h, o)
                .initRenderer();
    }

    ~SDLWindow()
    {
        if (glContext != nullptr)
            SDL_GL_DeleteContext(glContext);
        
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
    }

private:
    bool initSDL()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
          std::cout << "could not initialize SDL2 \n" << SDL_GetError() << "\n";
          return false;
        }

        return true;
    }

    SDLWindow& initWindow(const std::string& name, 
        const uint& width, 
        const uint& height, 
        const int& opts)
    {
        win = SDL_CreateWindow((const char*)name.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            opts);

        if (win == nullptr)
            std::cout << "Could not create Window\n" << SDL_GetError() << "\n";

        if ((opts & SDL_WINDOW_OPENGL) == SDL_WINDOW_OPENGL)
            glContext = SDL_GL_CreateContext(win);

        return *this;
    }

    SDLWindow& initRenderer()
    {
        rend = SDL_CreateRenderer(win, -1,
                SDL_RENDERER_ACCELERATED);

        if (rend == nullptr)
            std::cout << "Could not create Renderer\n" << SDL_GetError() << "\n";

        return *this;
    }
};

#endif
