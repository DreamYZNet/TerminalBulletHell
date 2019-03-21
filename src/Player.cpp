
#include "Player.h"

Player::Player(Stage &stage_) :Object(3,1), stage(stage_) {
    getGraphic().set(0,0,'^');
    getGraphic().set(1,0,'#');
    getGraphic().set(2,0,'^');
    getGraphic().fillFColor(10);
    getGraphic().setPriority(20);
    setHX(1);
    setHWidth(1);
    setHY(0);
    setHHeight(1);
}

void Player::shoot() {
    if (fireDelay == 0) {
        Bullet* bullet = new Bullet (0, 0, 90, 1, '|', 10);
        Bullet* bullet2 = new Bullet (2, 0, 90, 1, '|', 10);
        shoot(bullet);
        shoot(bullet2);
        fireDelay = maxFireDelay;
    }
}

void Player::shoot(Bullet* bullet, bool local) {
    if (local) {
        bullet->petX(getGX());
        bullet->petY(getGY());
    }
    stage.addObject(*bullet);
}

void Player::update() {
    if (fireDelay > 0)
        fireDelay--;
    //prevent from going out of bounds
    if (getGX() < 0) {
        setGX(0);
    }else if (getGX()+getWidth() > stage.getWidth()) {
        setGX(stage.getWidth()-getWidth());
    }else if (getGY() < 1) {
        setGY(1);
    }else if (getGY()+getHeight() > stage.getHeight()) {
        setGY(stage.getHeight()-getHeight());
    }
}
