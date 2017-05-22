#ifndef GAMEMAP_H
#define GAMEMAP_H


#include "tile.h"
#include <vector>

//objecto protegido?
class gameMap {
	private:
		int height;
		int width;
		std::vector<tile> casillas;
	public:
		gameMap(int *casilla, int size);
		gameMap(std::vector<int> &casilla_code);
		gameMap(int height, int width, std::vector<tile> &casillas); //para testeo
		gameMap(int height, int width); //pasarle el archivo xml y que complete casillas??
		void getNeightboors(tile &q, std::vector<tile*> &ady);
		tile getTile(int x, int y);
		tile* getTileP(int x, int y);
		tile* getTilePFromUnit(int x, int y);
		void printMap();
};

#endif
