
#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"
#include "Stage.h"
#include "Bullet.h"

class Player: public Object{

	public:
	    Player(Stage &stage);
        void update();
        void shoot();
	    void shoot(Bullet* bullet, bool local=true);

	private:
	    Stage& stage;
	    int fireDelay = 0;
	    int maxFireDelay = 5;

};

#endif
