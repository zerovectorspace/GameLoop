#ifndef _SDL_WINDOW_
#define _SDL_WINDOW_

#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <cstdint>

class SDLWindow{
    using u_int32 = std::uint_fast32_t;
    using String = std::string;

public:
    SDL_Window* win = nullptr;
    SDL_Renderer* rend = nullptr;

private:
    SDL_GLContext glContext = nullptr;

public:
    SDLWindow(
        const String& n = "Game Loop",
        const u_int32& w = 800,
        const u_int32& h = 600,
        const u_int32& o = SDL_WINDOW_SHOWN,
        const u_int32& r_o = SDL_RENDERER_ACCELERATED)
    {
        if (initSDL())
        {
            initWindow(n, w, h, o);

            if ((o & SDL_WINDOW_OPENGL) == 0)
                initRenderer(r_o);
        }
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

    SDLWindow& initWindow(const String& name,
        const u_int32& width,
        const u_int32& height,
        const u_int32& opts)
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
        {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

            glContext = SDL_GL_CreateContext(win);

            SDL_GL_SetSwapInterval(0);
        }

        return *this;
    }

    SDLWindow& initRenderer(const u_int32& opts)
    {
        rend = SDL_CreateRenderer(win, -1,
                opts);

        if (rend == nullptr)
            std::cout << "Could not create Renderer\n" << SDL_GetError() << "\n";

        return *this;
    }
};

#endif
