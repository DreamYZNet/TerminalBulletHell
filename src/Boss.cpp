
#include "Boss.h"

Boss::Boss(Stage &stage_) : Object(3,3), stage(stage_) {
    getGraphic().fill('*');
    getGraphic().fillFColor(12);
    getGraphic().setPriority(20);
}

void Boss::shoot(Bullet* bullet, bool local) {
    if (local) {
        bullet->petX(getGX());
        bullet->petY(getGY());
    }
    stage.addObject(*bullet);
}
