#include <iostream>
#include <thread>
#include <windows.h> //because screw linux users
#include <sstream>
#include "GameHandler.h"

namespace patch {
    template < typename T > std::string to_string( const T& n ) {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

//find the amount of ticks left until we are 1 frame forward in time
int timeToWait(clock_t lastTime, int fps) {
    return CLOCKS_PER_SEC/fps-(clock()-lastTime);
}

int main() {

    //variables for tracking time
    long int frame = 0;
    long int displays = 0;
    int fps = 60;
    double fpsDisplay = fps;
    clock_t lastUpdateTime = clock();
    clock_t lastDisplayTime = clock();
    int framesSinceDisplay = 1;

    SetConsoleTitle("Danmaku Project");
    GameHandler* gameHandler = new GameHandler(&gameHandler);

	while(true) {
        lastUpdateTime = clock();
        //displaying fps
        fpsDisplay = (CLOCKS_PER_SEC/(clock()-lastDisplayTime)+fpsDisplay*29)/30;
        std::string title = "Danmaku Project - fps:" + patch::to_string(static_cast<int>(fpsDisplay)) + " slows:" + patch::to_string(frame-displays);
        SetConsoleTitle(title.c_str());

        //update the game
        try{
            gameHandler->update();
        }catch(...){}
         //if were on schedule, or updating took too long, then display (but dont if were catching up)
        if (timeToWait(lastDisplayTime,fps) >= 0 || timeToWait(lastUpdateTime,fps) <= 0
                || -timeToWait(lastDisplayTime,fps)-(CLOCKS_PER_SEC/fps*framesSinceDisplay) <= 0
                || framesSinceDisplay > 3) {
            lastDisplayTime = clock();
            //display the game
            gameHandler->draw();
            displays++;
            framesSinceDisplay = 1;
        }else{
            framesSinceDisplay++;
        }

        //time shenanigans
        if (timeToWait(lastUpdateTime,fps) > 0 && framesSinceDisplay == 1)
            std::this_thread::sleep_for(std::chrono::milliseconds(timeToWait(lastUpdateTime,fps)));

        frame++;
	}

	return 0;
}











