
#include "Bullet.h"

Bullet::Bullet (double x, double y, double a, double v, char g, int c, double w, double h)
    :Object(x,y,w,h), angle(a), velocity(v) {
    getGraphic().fill(g);
    getGraphic().fillFColor(c);
}

void Bullet::update() {
    //the bullet moves
    petX(PhysicsMath::getAngledX(angle, velocity));
    petY(PhysicsMath::getAngledY(angle, velocity));
}

double Bullet::getAngle()    { return angle;    }
double Bullet::getVelocity() { return velocity; }
void Bullet::setAngle(double _angle)       { angle = _angle;       }
void Bullet::setVelocity(double _velocity) { velocity = _velocity; }

