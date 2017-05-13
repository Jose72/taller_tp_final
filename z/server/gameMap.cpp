#include "gameMap.h"
#include <iostream>


gameMap::gameMap(int height, int width, std::vector<tile> &casillas): height(height), 
width(width), casillas(casillas) {};


// vecinos
// x-1, y-1 | x, y-1   | x+1, y-1 |
//-----------------------------------
// x-1, y   | x, y     | x+1, y   |
//-----------------------------------
// x-1, y+1 | x, y+1   | x+1, y+1 | 


void gameMap::getNeightboors(tile &q, std::vector<tile*> &ady){
	//tomo el x,y de la casilla
	int x = q.getX();
	int y = q.getY();
	for (int dx = -1; dx < 2; dx++){
		for (int dy = -1; dy < 2; dy++){
			int new_x = x + dx;
			int new_y = y + dy;
		    int pos = new_x + new_y * width; //width tendria que ser cant de casillas horizontal
			//si x e y son positivos y la pos existe
			if (new_x >= 0 && new_y >= 0 && pos < (int) casillas.size() &&
			!(new_x == x && new_y == y) && (new_x < width) && (new_y < height)) {
				//la guardo
				ady.push_back(&casillas[pos]);
			}
		}
	}
}

tile gameMap::getTile(int x, int y){
	return casillas[x + y * width];
}

tile* gameMap::getTileP(int x, int y){
	return &casillas[x + y * width];
}