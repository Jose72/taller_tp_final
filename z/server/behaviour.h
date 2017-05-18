#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include "unit.h"


class behaviour {
	public:
		virtual void run() = 0; 
};



class moveUnit: public behaviour {
	void run(int x, int y, unit &u);
};


#endif



