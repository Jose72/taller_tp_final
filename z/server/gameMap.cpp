#include "gameMap.h"
#include <iostream>
#include <vector>
#include "math.h"


gameMap::gameMap(std::vector<int> &casilla_code){
	height = sqrt(casilla_code.size());
	width = sqrt(casilla_code.size());
	for (int i = 0; i < height; i++){
		for (int j = 0; i < width; i++){
			casillas.push_back(tile(i, j, casilla_code[i]));
		}
	}
}

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
			//si x e y son positivos, y no se pasan de cant de casillas, y la pos existe
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

tile* gameMap::getTilePFromUnit(int x, int y){
	int px;
	int py;
	for (px = 0; px < width; px++) {
		if ((px+1)*32 >= x) {
			break;
		}
	}
	for (py = 0; py < height; py++) {
		if ((py+1)*32 >= y) {
			break;
		}
	}
	return &casillas[px + py * width];
}

void gameMap::printMap(){
	for (unsigned int i = 0; i < casillas.size(); i++){
		casillas[i].printTile();
	}
}