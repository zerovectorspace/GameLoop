#ifndef __EVENTS__
#define __EVENTS__

#include <SDL2/SDL.h>

#include <unordered_map>

class Events
{
private:
    using EventMap = std::unordered_map<Uint32, void (Events::*)(SDL_Event&)>;

    EventMap event_map = {
        {
            SDL_KEYDOWN, &Events::keydown
        }
    };

    void keydown(SDL_Event& events)
    {
        std::cout << "Key Code: " << events.key.keysym.scancode << "\t" <<
            "Name: " << SDL_GetScancodeName(events.key.keysym.scancode) << "\n";
    }

public:
    void run(SDL_Event& events)
    {
        if (event_map.count(events.type))
            (this->*event_map[events.type])(events);
    }
};

#endif
