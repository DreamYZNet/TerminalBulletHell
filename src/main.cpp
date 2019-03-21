/*
Date: 5/23/2017
Problem Statement: Create a bullet hell game for the console
1. Create a time consistent game loop that tries to hold a consistent fps
2. Develop a class to manage the game and its loops ad updates
3. Design a way to display the game fast and efficiently with colors
4. Make screens that hold data for the various aspects, such as colors and characters
5. Add objects that hold x & y values that can be stored in a vector and displayed on the display
6. Adjust ways for such objects to shoot bullets
7. Manage functionality to check for collisions between the player and the bullets
8. Expand the player to allow input from the keyboard for movement and shooting functionality
9. Erupt new mathematical formulas to solve the gridded display with real angled 2 dimensional space travel
10. Evolve the game for multiple bullet patterns and a menu for them
11. Apply collision to create incredible and amazing death effects
12. Generate files with the all new file generator to bring the score and name of the best player straight to your hands
13. Establish your (my) game as properly optimized and bug free, and clean & commented for just myself to read in awe
14. Reinforce your chance of success with everything you just basically did
15. Invent a creative title for your project to shoe on the title bar
*/

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











