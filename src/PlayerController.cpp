
#include "PlayerController.h"

PlayerController::PlayerController(Player &player_): player(player_){}

void PlayerController::update() {
    if (GetAsyncKeyState(VK_SPACE)) {
        player.shoot();
    }
    //pressing only activates the button once until release
    if (GetAsyncKeyState(VK_LEFT)) {
        if (tapLeft == false) {
            player.petX(-1);
            tapLeft = true;
        }
    }else{
        tapLeft = false;
    }
    if (GetAsyncKeyState(VK_RIGHT)) {
        if (tapRight == false) {
            player.petX(1);
            tapRight = true;
        }
    }else{
        tapRight = false;
    }
    if (GetAsyncKeyState(VK_UP)) {
        if (tapUp == false) {
            player.petY(-1);
            tapUp = true;
        }
    }else{
        tapUp = false;
    }
    if (GetAsyncKeyState(VK_DOWN)) {
        if (tapDown == false) {
            player.petY(1);
            tapDown = true;
        }
    }else{
        tapDown = false;
    }
}
