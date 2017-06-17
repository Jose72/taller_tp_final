#include "createHandler.h"
#include "unitBuilder.h"
#include "iostream"


//chequear que el tech lvl no te baje


int createHandler::createActualize(unit &creator, std::map<int, unit*> &units, 
int &unit_id_c, int time, infoGame &ip){
	//if (creator.getClassId() != BUILDING) return 1;
	creator.updateCreationTimer(time, ip.getCapturedTer(creator.getOwner())); //avanzo el timer
	//si llego el timer a 0 y no alcnzo limite de unidades
	if (creator.canCreate() && !ip.maxPopReached(creator.getOwner())){
		unitBuilder ub;
		//chequear donde se va a crear la unidad (posicion)
		unit *u = ub.build(creator.unitToCreate(), creator.getOwner(), 
		creator.getCenterX() + creator.getRadius() + 16, creator.getCenterY());
		units.insert(std::pair<int,unit*>(unit_id_c,u));
		unit_id_c++;//incremento id_units
		ip.incrementUnitsCount(creator.getOwner()); //incremento cant unidades player
		//reseteo el timer
		creator.resetTimer();
	}
	return 0;
}