#include "createHandler.h"
#include "unitBuilder.h"
#include "iostream"


createHandler::createHandler(unitBuilder &ub, infoUnits &u_info): ub(ub), u_info(u_info) {}

int createHandler::createRobotActualize(unit &creator, std::map<int, unit*> &units, int &unit_id_c, infoGame &ip){
	//chequear donde se va a crear la unidad (posicion)
	int q_to_create = u_info.getQuantToFab(creator.unitToCreate());
	int dx = 16;
	int dy = 18;
	for (int i = 0; i < q_to_create; ++i){
		unit *u = ub.build(creator.unitToCreate(), creator.getOwner(), 
		creator.getX() + creator.getWidth() + dx, creator.getY() + dy*i);
		//std::cout << "unti creted: " << creator.unitToCreate() << std::endl;
		units.insert(std::pair<int,unit*>(unit_id_c,u));
		unit_id_c++;//incremento id_units
		ip.incrementUnitsCount(creator.getOwner()); //incremento cant unidades player
	}
	
	//reseteo el timer
	creator.resetTimer();
	return 0;
}

int createHandler::createVehicleActualize(unit &creator, std::map<int, unit*> &units, int &unit_id_c, infoGame &ip){
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

	//incremento solo una vez
	ip.incrementUnitsCount(creator.getOwner());
	
	//reseteo el timer
	creator.resetTimer();
	return 0;
}


int createHandler::createActualize(unit &creator, std::map<int, unit*> &units, 
int &unit_id_c, int time, infoGame &ip){
	//if (creator.getClassId() != BUILDING) return 1;
	creator.updateCreationTimer(time, ip.getCapturedTer(creator.getOwner())); //avanzo el timer
	//si llego el timer a 0 y no alcanzo limite de unidades
	if (creator.canCreate() && !ip.maxPopReached(creator.getOwner())){
		switch(u_info.getClassCode(creator.unitToCreate())){
			case ROBOT:
				createRobotActualize(creator, units, unit_id_c, ip);
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