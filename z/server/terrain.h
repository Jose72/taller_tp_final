#ifndef TERRAIN_H
#define TERRAIN_H

//para los codigos de unidades
#include "unit.h"

//esto en un xml?
#define TIERRA 6
#define PRADERA 0
#define NIEVE 3
#define AGUA 1
#define PANTANO 5
#define LAVA 2
#define CARRETERA 7
#define ASFALTO 4

#define TIERRA_FACTOR 1
#define PRADERA_FACTOR 1
#define NIEVE_FACTOR 1
#define AGUA_FACTOR 0.7
#define PANTANO_FACTOR 0.7
#define LAVA_FACTOR 0
#define CARRETERA_FACTOR 1.5
#define ASFALTO_FACTOR 1.5

class terrain{
	protected:
		int t_type; //tipo de terreno, o codigo de terreno
		bool passable_by_robot;
		bool passable_by_vehicle;
		double terrain_factor; //factor de velocidad en el terreno
	public:
		terrain(int terrain_code);
		terrain(int t_type, bool pb_robot, bool pb_vehicle, double t_factor);
		void construct(int t_type, bool pb_robot, bool pb_vehicle, double t_factor);
		bool isPassable(int unit_code);
		double getTerrainFactor();
};

/*
// codigo viejo, guardado por la dudas
//tipos de terrenos

class terrainPradera: public terrain{
	public:
		terrainPradera();
};

class terrainAgua: public terrain{
	public:
		terrainAgua();
};

class terrainLava: public terrain{
	public:
		terrainLava();
};
*/

#endif