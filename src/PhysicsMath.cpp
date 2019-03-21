
#include "PhysicsMath.h"

double PhysicsMath::getAngledX(double angle, double length) {
    return cos(angle * PI / 180.0) * length;
}

double PhysicsMath::getAngledY(double angle, double length) {
    return -sin(angle * PI / 180.0) * length;
}

double PhysicsMath::getRotateX(double angle, double length, double degrees) {
    //70% sure there is a more efficient way to calculate this
    double x = getAngledX(angle-180, length);
    x += getAngledX(angle+degrees, length);
    return x;
}

double PhysicsMath::getRotateY(double angle, double length, double degrees) {
    //70% sure there is a more efficient way to calculate this
    double y = getAngledY(angle-180, length);
    y += getAngledY(angle+degrees, length);
    return y;
}

double PhysicsMath::getAngle(double x1, double y1, double x2, double y2) {
    return atan2(y1 - y2, x2 - x1) * 180 / PI;
}
