#ifndef GAMEMAP_H
#define GAMEMAP_H


#include "tile.h"
#include <vector>
#include <map>
#include "unit.h"

//objecto protegido?
class gameMap {
	private:
		int height;
		int width;
		std::vector<tile> casillas;
		
		std::vector<tile> h_casillas;
	public:
		gameMap();
		gameMap(int *casilla, int size);
		gameMap(std::vector<int> &casilla_code);
		gameMap(int height, int width, std::vector<tile> &casillas); //para testeo
		gameMap(int height, int width); //pasarle el archivo xml y que complete casillas??
		void getNeightboors(tile &q, std::vector<tile*> &ady);
		tile getTile(int x, int y);
		tile* getTileP(int x, int y);
		tile* getTilePFromUnit(double x, double y);
		void printMap();
		void setBlocking(std::map<int,unit*> &units);
		void seePassableForUnit(int unit_code);
		//para mejora
		void setHighResMap(); //no use yet
		void getNeightboorsHRes(tile &q, std::vector<tile*> &ady);
		void setBlockingHRes(std::map<int,unit*> &units);
		tile getTileHRes(int x, int y);
		tile* getTilePHRes(int x, int y);
		tile* getTilePFromUnitHRes(double x, double y);
};

#endif
