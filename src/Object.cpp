
#include "Object.h"

Object::Object(int w, int h, int priority)
    :graphic(w,h,priority), x(0), y(0), width(w), height(h)
    ,hX(0), hY(0), hWidth(w), hHeight(h){}
Object::Object(int x, int y, int w, int h, int priority)
    :graphic(w,h,priority), x(x), y(y), width(w), height(h)
    ,hX(0), hY(0), hWidth(w), hHeight(h){}

double Object::getGX() {
    if (parent != 0)
        return parent->getGX();
    return getX();
}

double Object::getGY() {
    if (parent != 0)
        return parent->getGY();
    return getY();
}

double Object::getX()        { return x;            }
double Object::getY()        { return y;            }
double Object::getWidth()    { return width;        }
double Object::getHeight()   { return height;       }
double Object::getGHX()      { return getGX() + hX; }
double Object::getGHY()      { return getGY() + hY; }
double Object::getHWidth()   { return hWidth;       }
double Object::getHHeight()  { return hHeight;      }
Screen& Object::getGraphic() { return graphic;      }
Object& Object::getParent()  { return *parent;      }
void Object::setGX(double val)       { x += val-getGX(); }
void Object::setGY(double val)       { y += val-getGY(); }
void Object::setX(double val)        { x = val;          }
void Object::setY(double val)        { y = val;          }
double Object::petX(double val)      { return x+=val;    }
double Object::petY(double val)      { return y+=val;    }
void Object::setWidth(double val)    { width = val;      }
void Object::setHeight(double val)   { height = val;     }
void Object::setHX(double val)       { hX = val;         }
void Object::setHY(double val)       { hY = val;         }
void Object::setHWidth(double val)   { hWidth = val;     }
void Object::setHHeight(double val)  { hHeight = val;    }
void Object::setGraphic(Screen& val) { graphic = val;    }
void Object::setParent(Object& obj)  { parent = &obj;    }
