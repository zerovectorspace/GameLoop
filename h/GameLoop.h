#ifndef _GAME_LOOP_
#define _GAME_LOOP_

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

class GameLoop{
private:
    int updatesPerSecond = 60;
    int singleFrameTimeInMS = 0;
    const int maxFrameSkip = 5;
    int loops = 0; 

    Uint32 nextFrameTime = 0;
    Uint32 prevFrameTime = 0;

    std::string intpolSpeed = "medium";
    int prevIntpol = -1;

    Uint32 oneSecond = 0;
    Uint32 drawCount = 0;

    bool isFirstRun = true;

    
    auto& setUPS(const uint& u){
        if (u > 0 && u <= 240)
        {
            updatesPerSecond = u;
            
            if (u % 2 == 0)
                updatesPerSecond--;

            singleFrameTimeInMS = static_cast<int>(1000 / updatesPerSecond);
        }
        return *this;
    }
    auto& checkForQuit(){
        switch (e.type)
        {
            case SDL_QUIT:
            {
                isRunning = false;
                break;
            }
            case SDL_WINDOWEVENT:
            {
                if (e.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
                {
                    SDL_Event f;
                    f.type = SDL_WINDOWEVENT;
                    f.window.event = SDL_WINDOWEVENT_FOCUS_GAINED;
                    SDL_WaitEvent(&f);
                }
                break;
            }
        }
        return *this;
    }
    auto& secondTimerMaster(){
        // If one second has passed
        if (now > oneSecond + 1000)
        {
            secondTimer();
            oneSecond = now;
        }
    	return *this;
    }
    auto& calcDeltaTime()
    {
    	// a way to allow us to specify the velocity of our 
    	//objects in pixels per second. This keeps the animation distance
    	//constant when the frame rate changes
    	deltaTime = static_cast<float>((now - prevFrameTime) / 1000.0f);
    	return *this;
    }
    auto& intAndDraw(const int& i)
    {
        calcDeltaTime()
        	.interpolate()
            .draw();
        prevIntpol = i;
        drawCount++;
        return *this;
    }
    auto& mainLoop()
    {
        //Start the loop while isRunning is true
        while (isRunning)
        {
            now = SDL_GetTicks();
            //This function holds our input handling
            //We can also put this above the updatePositions() call
            //But that slows down the inputs.
            while (SDL_PollEvent(&e))
            {
                checkForQuit()
                    .inputs();
            }

            //loops is the number of time we have skipped frames
            loops = 0;
            //This loop determines when to update the position
            //This is how we separate the drawing and the position updating
            while( now > nextFrameTime && loops < maxFrameSkip) 
            {
                //Finally update the position of our objects
                calcDeltaTime()
                	.updatePositions()
                	.collisions()
                	.secondTimerMaster();

                //nextFrameTime is the time in MS we need to pass to update
                nextFrameTime += singleFrameTimeInMS;
                //This is the time right now
                prevFrameTime = now;
                //If we are stuck here because the frame rate slows we need to
                //break out if loops is > maxFrameSkip
                loops++;
            }
            //This is basically the percentage between frames we currently are
            interpolation = static_cast<float>( now + singleFrameTimeInMS - nextFrameTime )
                / static_cast<float>( singleFrameTimeInMS );

            //convert that percentage to an integer to make it easy to test
            int ip = static_cast<int>(interpolation * 100);

            if (ip < 10)
                ip = 0;
            //Finally we can draw if the following tests have passed
            //Check against previous interpolation so we don't render
            //the same thing more than once
            //Play around with these to find an ideal interpolation
            if ( (intpolSpeed == "slow" || intpolSpeed == "off") &&
                (ip != prevIntpol && (ip == 0 || ip == 50)) )
            {
                if (ip == 50 && intpolSpeed == "off")
                    prevIntpol = ip;
                else
                    intAndDraw(ip);
            }
            else if ( (intpolSpeed == "medium") &&
                (ip != prevIntpol && (ip == 0 || ip == 25 || ip == 50 || ip == 75)) )
            {
                intAndDraw(ip);
            }
            else if (intpolSpeed == "fast")
            {
                intAndDraw(ip);
            }
        }
        return *this;
    }

public:
    GameLoop(const uint& ups=60, const std::string& speed="medium"){
        setUPS(ups);

        if (speed == "off" || speed == "slow" || speed == "medium" || speed == "fast")
            intpolSpeed = speed;

    }   
    virtual ~GameLoop(){}
    
    SDL_Event e;
    SDL_Window* win = NULL;

    Uint32 now = 0;
    float deltaTime = 0.0;
    float interpolation = 0.0;
    bool isRunning = true;

    auto& start(){
        init()
            .mainLoop();

        return *this;
    }
    auto& start(SDLWindow& sdlWin){
        if (sdlWin.win != NULL)
            win = sdlWin.win;

        start();

        return *this;
    }
    
    virtual GameLoop& init(){
        return *this;
    }
    virtual GameLoop& secondTimer(){
    	// This function is called every second
    	consoleOutput();
    	return *this;
    }
    virtual GameLoop& consoleOutput(){
        //To show what is happening in the terminal
        //shows the number of times our interpolated 
        //objects have been drawn, this is called every second
        if (isFirstRun)
        {
            std::cout << "Time Passed\tFrames Drawn\tFrame Skipped\n";
            isFirstRun = false;
        }

        std::cout << now/1000 << "\t\t" << drawCount << "\t\t" << loops << "\n";
        drawCount = 0;

        return *this;
    }
    virtual GameLoop& inputs(){
        return *this;
    }
    virtual GameLoop& collisions(){
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
