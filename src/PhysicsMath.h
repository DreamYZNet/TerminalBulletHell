
#ifndef PHYSICSMATH_H
#define PHYSICSMATH_H

#include <cmath>

const static double PI = 3.141592653;

class PhysicsMath {

    public:
        //Get relative x/y position toward the angle at the length distance
        static double getAngledX(double angle, double length);
        static double getAngledY(double angle, double length);
        //Get relative x/y by rotating along a center by degrees
        static double getRotateX(double angle, double length, double degrees);
        static double getRotateY(double angle, double length, double degrees);
        //Find angle between 2 points
        static double getAngle(double x1, double y1, double x2, double y2);

    private:
        PhysicsMath();

};

#endif // PHYSICSMATH_H
