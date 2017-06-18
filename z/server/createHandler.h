#ifndef CREATEHANDLER_H
#define CREATEHANDLER_H

#include "unit.h"
#include <map>
#include "infoGame.h"

class createHandler{
		int createcommonActualize(unit &creator, std::map<int, unit*> &units, 
			int &unit_id_c, infoGame &ip);
		int createVehicleActualize(unit &creator, std::map<int, unit*> &units, 
			int &unit_id_c, infoGame &ip);
	public:
		int createActualize(unit &creator, std::map<int, unit*> &units, 
			int &unit_id_c, int time, infoGame &ip);
};

#endif