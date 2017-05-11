#include "gameMap.h"

// vecinos
// x-1, y-1 | x, y-1   | x+1, y-1 |
//-----------------------------------
// x-1, y   | x, y     | x+1, y   |
//-----------------------------------
// x-1, y+1 | x, y+1   | x+1, y+1 | 


void gameMap::getNeightboors(tile &q, std::vector<tile> &ady){
	//tomo el x,y de la casilla
	int x = q.getX();
	int y = q.getY();
	for (int dx = -1; dx < 2; dx++){
		for (int dy = -1; dx < 2; dx++){
			int new_x = x + dx;
			int new_y = y + dy;
		    int pos = x + y * width; //width tendria que ser cant de casillas horizontal
			//si x e y son positivos y la pos existe
			if (new_x >= 0 && new_y >= 0 && pos < (int) casillas.size()) {
				tile q = casillas[pos];
				//si es pasable, la guardo
				if (q.isPassable()) ady.push_back(q);
			}
		}
	}
}

tile gameMap::getTile(int x, int y){
	return casillas[x + y * width];
}