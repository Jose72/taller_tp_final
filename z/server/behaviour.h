#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include "unit.h"


class behaviour {
};



class moveUnit: public behaviour {
	void run(int x, int y, unit &u);
};


#endif



