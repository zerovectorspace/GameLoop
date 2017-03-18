#ifndef __EVENTS__
#define __EVENTS__

#include <SDL2/SDL.h>
#include <unordered_map>

class Events
{
private:
    using EventMap = std::unordered_map<Uint32, void (Events::*)(SDL_Event&)>;

    /**
     * Map of event codes to member functions
     */
    EventMap event_map = {
        {
            SDL_KEYDOWN, &Events::keydown
        }
    };

public:
    /**
     * Call the event defined in event_map
     * @param events
     */
    void run(SDL_Event& events)
    {
        if (event_map.count(events.type))
            (this->*event_map[events.type])(events);
    }

private:
    void keydown(SDL_Event& events)
    {
        std::cout << "Key Code: " << events.key.keysym.scancode << "\t" <<
            "Name: " << SDL_GetScancodeName(events.key.keysym.scancode) << "\n";
    }

};

#endif
