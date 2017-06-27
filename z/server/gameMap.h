#ifndef GAMEMAP_H
#define GAMEMAP_H


#include "tile.h"
#include <vector>
#include <map>
#include "unit.h"


class gameMap {
	private:
		int height;
		int width;
		std::vector<tile> casillas;
	public:
		gameMap();
		gameMap(int *casilla, int size);
		gameMap(std::vector<int> &casilla_code);
		gameMap(int height, int width, std::vector<tile> &casillas);
		gameMap(int height, int width);
		void getNeightboors(tile &q, std::vector<tile*> &ady);
		tile* getTileP(int x, int y);
		tile* getTilePFromUnit(double x, double y);
		void printMap();
		void setBlocking(std::map<int,unit*> &units);
		void setUnitAsBlocking(unit *u);
		bool impossibleTile(int x, int y, int class_u);
		void releaseUnitBlocking(unit *u);
		tile* getClosestPassableTile(int x, int y, unit* u);
};

#endif
