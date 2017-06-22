#ifndef CREATEHANDLER_H
#define CREATEHANDLER_H

#include "unit.h"
#include <map>
#include "unitBuilder.h"
#include "infoGame.h"
#include "infoUnits.h"

class createHandler{
	private:
		unitBuilder &ub;
		infoUnits &u_info;
		
		int createRobotActualize(unit &creator, std::map<int, unit*> &units, 
			int &unit_id_c, infoGame &ip);
		int createVehicleActualize(unit &creator, std::map<int, unit*> &units, 
			int &unit_id_c, infoGame &ip);
	public:
		createHandler(unitBuilder &ub, infoUnits &u_info);
		int createActualize(unit &creator, std::map<int, unit*> &units, 
			int &unit_id_c, int time, infoGame &ip);
};

#endif