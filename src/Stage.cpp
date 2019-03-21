
#include "Stage.h"

Stage::Stage (int w, int h): width(w), height(h){}

void Stage::update() {
    for (Object *obj: objects) {
        //update all objects
        obj->update();
        //delete objects outside of stage
        if (obj->getGX() >= getWidth() || obj->getGY() >= getHeight()
                || obj->getGX()+obj->getWidth()-1 <= 0 || obj->getGY()+obj->getHeight()-1 <= 0) {
            objects.erase(std::remove(objects.begin(), objects.end(), obj), objects.end());
        }
    }
}

void Stage::addObject(Object &obj) {
    objects.push_back(&obj);
}

int Stage::getHeight ()                   { return height;  }
int Stage::getWidth ()                    { return width;   }
std::vector<Object*>& Stage::getObjects() { return objects; }
