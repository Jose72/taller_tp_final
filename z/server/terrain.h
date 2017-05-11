#ifndef TERRAIN_H
#define TERRAIN_H

//para ver si pasan por el terreno
#define ROBOT 4
#define VEHICLE 5

class terrain{
	private:
		bool passable_by_robot;
		bool passable_by_vehicle;
		double terrain_factor; //factor de velocidad en el terreno
	public:
		bool isPassable(int unit_code);
		double getTerrainFactor();
};

#endif