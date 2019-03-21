
#ifndef BULLET_H
#define BULLET_H

#include "Object.h"
#include "PhysicsMath.h"

class Bullet: public Object {

	public:
	    Bullet (double x, double y, double angle, double velocity, char visual='O', int color=-1, double width=1, double height=1);
        void update();

    public:
		double getAngle();
		double getVelocity();
		void setAngle(double);
		void setVelocity(double);

	private:
		double angle;
		double velocity;

};

#endif
