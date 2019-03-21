
#ifndef STAGE_H
#define STAGE_H

#include "Object.h"
#include <vector>
#include <algorithm> //for remove function

class Stage {

	public:
		Stage(int w, int h);
	    void update();
		void addObject(Object&);

		int getHeight();
		int getWidth();
        std::vector<Object*> &getObjects();

	private:
		int height = 10;
		int width = 10;
	    std::vector<Object*> objects;

};

#endif
