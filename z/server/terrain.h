#ifndef TERRAIN_H
#define TERRAIN_H

//codigo de unidad para ver si pasan por el terreno
#define ROBOT 4
#define VEHICLE 5

//esto en un xml?
#define TIERRA 6
#define PRADERA 7
#define NIEVE 8
#define AGUA 9
#define PANTANO 10
#define LAVA 11
#define CARRETERA 12
#define ASFALTO 13

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
		terrain(int t_type, bool pb_robot, bool pb_vehicle, double t_factor);
		bool isPassable(int unit_code);
		double getTerrainFactor();
};


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


#endif