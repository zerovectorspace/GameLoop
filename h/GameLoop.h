#ifndef _GAME_LOOP_
#define _GAME_LOOP_

#include <iostream>

class GameLoop{
private:
    SDL_Event e;

    const int updatesPerSecond = 60;
    const int singleFrameTimeInMS = 1000 / updatesPerSecond;
    const int maxFrameSkip = 5;
    int loops = 0; 

    Uint32 nextFrameTime = 0;
    Uint32 prevFrameTime = 0;

    int prevIntpol = -1;

    Uint32 timerNow = 0;
    Uint32 drawCount = 0;

    bool isRunning = true;

    GameLoop& checkForQuit(){
        SDL_PollEvent(&this->e);
        if (this->e.type == SDL_QUIT)
        {
            isRunning = false;
        }
        else if (this->e.type == SDL_WINDOWEVENT)
        {
            if (this->e.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
            {
                SDL_Event f;
                f.type = SDL_WINDOWEVENT;
                f.window.event = SDL_WINDOWEVENT_FOCUS_GAINED;
                SDL_WaitEvent(&f);
            }
        }
        return *this;
    }
    GameLoop& mainLoop()
    {
        //To show what is happening in the terminal
        std::cout << "Frames Drawn\tDelta\t\tInterpolation\n";
        //Start the loop while isRunning is true
        while (this->isRunning)
        {
            //this is a timer that shows the number of times our interpolated 
            //objects have been drawn every second
            if (SDL_GetTicks() > timerNow + 1000)
            {
                std::cout << drawCount << "\r\t\t" << deltaTime << "\t\t" << interpolation << "\n";
                drawCount = 0;
                timerNow = SDL_GetTicks();
            }
            //This function holds our input handling
            //We can also put this above the updatePositions() call
            //But that slows down the inputs.
            this->checkForQuit();
            this->inputs();

            //loops is the number of time we have skipped frames
            this->loops = 0;
            // a way to allow us to specify the velocity of our 
            //objects in pixels per second. This keeps the animation distance
            //constant when the frame rate changes
            this->deltaTime = float(SDL_GetTicks() - this->prevFrameTime) / 1000.0f;

            //This loop determines when to update the position
            //This is how we separate the drawing and the position updating
            while( SDL_GetTicks() > nextFrameTime && loops < maxFrameSkip) 
            {
                //Finally update the position of our objects
                this->updatePositions();

                //nextFrameTime is the time in MS we need to pass to update
                nextFrameTime += singleFrameTimeInMS;
                //This is the time right now
                prevFrameTime = SDL_GetTicks();
                //If we are stuck here because the frame rate slows we need to
                //break out if loops is > maxFrameSkip
                loops++;
            }
            //This is basically the percentage between frames we currently are
            interpolation = float( SDL_GetTicks() + singleFrameTimeInMS - nextFrameTime )
                / float( singleFrameTimeInMS );

            //convert that percentage to an integer to make it easy to test
            int ip = int(interpolation * 10);


            //Finally we can draw if the following tests have passed
            //Check against previous interpolation so we don't render
            //the same thing more than once
            //Play around with these to find an ideal interpolation

            //draws on 0% and 50%
            if ( (ip == 5 || ip == 0) && ip != prevIntpol )

            //draws on 0%, 30%, 60%, 90%
            // if ( (ip == 0 || ip == 3 || ip == 6 || ip == 9) && 
            //   ip != prevIntpol )

            //draw as fast as our hardware can
            // if (true)
            {
                //finally do the interpolation calculation
                this->interpolate();
                //make the interpolation current
                prevIntpol = ip;
                //Aaaaaand draw!
                this->draw();
            }

        }
    }

public:
    GameLoop(){
        this->mainLoop();        
    }
    ~GameLoop(){}
    
    float deltaTime = 0;
    float interpolation = 0;


    virtual GameLoop& inputs(){
        return *this;
    }
    virtual GameLoop& updatePositions(){
        return *this;
    }
    virtual GameLoop& interpolate(){
        return *this;
    }
    virtual GameLoop& draw(){
        return *this;
    }
};


#endif