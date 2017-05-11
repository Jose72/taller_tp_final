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
		gameMap(int height, int width, std::vector<tile> &casillas); //para testeo
		gameMap(int height, int width); //pasarle el archivo xml y que complete casillas??
		void getNeightboors(tile &q, std::vector<tile> &ady);
		tile getTile(int x, int y);
};

#endif
