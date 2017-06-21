#include "createHandler.h"
#include "unitBuilder.h"
#include "iostream"


int createHandler::createcommonActualize(unit &creator, std::map<int, unit*> &units, int &unit_id_c, infoGame &ip){
	unitBuilder ub;
	//chequear donde se va a crear la unidad (posicion)
	unit *u = ub.build(creator.unitToCreate(), creator.getOwner(), 
	creator.getCenterX() + creator.getRadius() + 16, creator.getCenterY());
	//std::cout << "unti creted: " << creator.unitToCreate() << std::endl;
	units.insert(std::pair<int,unit*>(unit_id_c,u));
	unit_id_c++;//incremento id_units
	ip.incrementUnitsCount(creator.getOwner()); //incremento cant unidades player
	//reseteo el timer
	creator.resetTimer();
	return 0;
}

int createHandler::createVehicleActualize(unit &creator, std::map<int, unit*> &units, int &unit_id_c, infoGame &ip){
	unitBuilder ub;
	//chequear donde se va a crear la unidad (posicion)
	//creo vehiculo
	unit *u = ub.build(creator.unitToCreate(), creator.getOwner(), 
	creator.getCenterX() + creator.getRadius() + 16, creator.getCenterY());
	units.insert(std::pair<int,unit*>(unit_id_c,u));
	unit_id_c++;//incremento id_units
	
	
	//creo driver
	unit *driv = ub.build(GRUNT, creator.getOwner(), 
	creator.getCenterX() + creator.getRadius() + 16, creator.getCenterY());
	driv->instantDrive(u);
	units.insert(std::pair<int,unit*>(unit_id_c, driv));
	unit_id_c++;//incremento id_unit
	
	//ip.incrementUnitsCount(creator.getOwner()); 
	
	
	ip.incrementUnitsCount(creator.getOwner());
	
	//reseteo el timer
	creator.resetTimer();
	return 0;
}


int createHandler::createActualize(unit &creator, std::map<int, unit*> &units, 
int &unit_id_c, int time, infoGame &ip){
	//if (creator.getClassId() != BUILDING) return 1;
	creator.updateCreationTimer(time, ip.getCapturedTer(creator.getOwner())); //avanzo el timer
	//si llego el timer a 0 y no alcnzo limite de unidades
	if (creator.canCreate() && !ip.maxPopReached(creator.getOwner())){
		switch(getClassCodeFromUnit(creator.unitToCreate())){
			case ROBOT:
				createcommonActualize(creator, units, unit_id_c, ip);
				return 0;
			case VEHICLE:
				createVehicleActualize(creator, units, unit_id_c, ip);
				return 0;
			default:
				return 0;
		}
	}
	return 0;
}