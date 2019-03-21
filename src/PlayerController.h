
#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "Player.h"
#include <windows.h>

class PlayerController {

    public:
        PlayerController(Player &player);
        void update();

    private:
        Player &player;
        bool tapLeft = false;
        bool tapRight = false;
        bool tapUp = false;
        bool tapDown = false;

};

#endif // PLAYERCONTROLLER_H
