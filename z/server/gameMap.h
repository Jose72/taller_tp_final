#ifndef GAMEMAP_H
#define GAMEMAP_H


#include "tile.h"
#include <vector>

//objecto protegido?
class gameMap {
	private:
		std::vector<tile> casillas;
	public:
		void getNeightboors(tile &q, std::vector<tile> &ady);
		tile getTile(int x, int y);
};

#endif
