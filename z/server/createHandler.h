#ifndef CREATEHANDLER_H
#define CREATEHANDLER_H

#include "unit.h"
#include <map>

class createHandler{
	public:
		int createActualize(unit &creator, std::map<int, unit*> &units, int &unit_id_c, int time);
};

#endif