#include "createHandler.h"
#include "unitBuilder.h"
#include "iostream"





int createHandler::createActualize(unit &creator, std::map<int, unit*> &units, int &unit_id_c, int time){
	if (creator.getClassId() != BUILDING) return 1;
	creator.actualizeTimer(time); //avanzo el timer
	
	if (creator.canCreate()){
		std::cout << "crea unidad" << std::endl;
		unitBuilder ub;
		//chequear donde se va a crear la unidad (posicion)
		unit *u = ub.build(creator.unitToCreate(), creator.getOwner(), creator.getX(), creator.getY()+32);
		units.insert(std::pair<int,unit*>(unit_id_c,u));
		unit_id_c++;//incremento id_units
		//reseteo el timer
		creator.resetTimer();
	}
	return 0;
}