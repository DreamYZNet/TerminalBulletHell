
#ifndef OBJECT_H
#define OBJECT_H

#include "Screen.h"

class Object {

    public:
        Object(int width, int height, int priority = 0);
        Object(int x, int y, int width, int height, int priority = 0);

        virtual void update(){}

    public:
        double getGX(); //return global x (based on parent)
        double getGY(); //return global y (based on parent)
        double getX();
        double getY();
        double getWidth();
        double getHeight();
        //hitbox values
        double getGHX();
        double getGHY();
        double getHWidth();
        double getHHeight();
        Screen &getGraphic();
        Object &getParent();
        void setGX(double val);
        void setGY(double val);
        void setX(double val);
        void setY(double val);
        void setWidth(double val);
        void setHeight(double val);
        void setHX(double val);
        void setHY(double val);
        void setHWidth(double val);
        void setHHeight(double val);
        void setGraphic(Screen& val);
        void setParent(Object& obj);
        double petX(double val);
        double petY(double val);

    private:
        double x;
        double y;
        double width;
        double height;
        double hX;
        double hY;
        double hWidth;
        double hHeight;
        Screen graphic;
        Object* parent = nullptr;

};

#endif // OBJECT_H
