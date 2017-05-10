#ifndef TERRAIN_H
#define TERRAIN_H


class Terrain{
	private:
		bool passable;
		double terrain_factor; //factor de velocidad en el terreno
	public:
		bool isPassable();
		double getTerrainFactor();
};

#endif