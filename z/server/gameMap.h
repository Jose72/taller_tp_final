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
		gameMap(int height, int width, std::vector<tile> &casillas); //para testeo
		gameMap(int height, int width); //pasarle el archivo xml y que complete casillas??
		int getMapDimension();
		void getNeightboors(tile &q, std::vector<tile*> &ady);
		void getNeightboorsNoDiagonal(tile &q, std::vector<tile*> &ady);
		tile* getTileP(int x, int y);
		tile* getTilePFromUnit(double x, double y);
		void printMap();
		void setBlocking(std::map<int,unit*> &units);
		void setUnitAsBlocking(unit *u);
		void seePassableForUnit(int unit_code);
		bool impossibleTile(int x, int y, int class_u);
		void releaseUnitBlocking(unit *u);
		tile* getClosestPassableTile(int x, int y, int c_unit);
};

#endif
