
#ifndef BOSS_H
#define BOSS_H

#include "Object.h"
#include "Stage.h"
#include "Bullet.h"

class Boss: public Object {

	public:
	    Boss(Stage &stage);
	    void shoot(Bullet* bullet, bool local=true);

	private:
	    Stage& stage;

};

#endif
