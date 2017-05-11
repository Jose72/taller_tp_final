#include "terrain.h"

terrain::terrain(int terrain_code){
	//el switch queda medio feo, ver si hay mejor forma (algun patron??)
	switch(terrain_code){
		case(TIERRA):
			this->construct(TIERRA, true, true, TIERRA_FACTOR);
		case(AGUA):
			this->construct(AGUA, true, false, AGUA_FACTOR);
		case(LAVA):
			this->construct(LAVA, false, false, LAVA_FACTOR);
	}
}

void terrain::construct(int t_type, bool pb_robot, bool pb_vehicle, double t_factor){
	t_type = t_type;
	passable_by_robot = pb_robot;
	passable_by_vehicle = pb_vehicle;
	terrain_factor = t_factor;
}

terrain::terrain(int t_type, bool pb_robot, bool pb_vehicle, double t_factor): 
t_type(t_type), passable_by_robot(pb_robot), passable_by_vehicle(pb_vehicle), 
terrain_factor(t_factor) {};

bool terrain::isPassable(int unit_code){
	if (unit_code == ROBOT) return passable_by_robot;
	if (unit_code == VEHICLE) return passable_by_vehicle;
	return false;
}



/*
//codigo viejo, guardado por las dudas
//constructores de los terrenos

terrainPradera::terrainPradera(): terrain(PRADERA, true, true, 
PRADERA_FACTOR) {};

terrainAgua::terrainAgua(): terrain(AGUA, true, false, 
AGUA_FACTOR) {};

terrainLava::terrainLava(): terrain(LAVA, false, false, 
LAVA) {};
*/