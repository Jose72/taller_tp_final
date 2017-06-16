#include "gameMap.h"
#include <iostream>
#include <vector>
#include "math.h"
#include <iostream>

gameMap::gameMap(){}

gameMap::gameMap(std::vector<int> &casilla_code){
	height = sqrt(casilla_code.size());
	width = sqrt(casilla_code.size());
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			casillas.push_back(tile(j, i, casilla_code[j + i * width]));
		}
	}
}

gameMap::gameMap(int height, int width, std::vector<tile> &casillas): height(height), 
width(width), casillas(casillas) {};

gameMap::gameMap(int *cas, int size) {
	height = sqrt(size);
	width = height;
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			casillas.push_back(tile(j, i, *(cas + j + i * width)));
		}
	}
};



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
	int s = casillas.size();
	
	int aux = x - 1 + (y - 1) * width;
	if ((aux < s - 1) || (aux >= 0)){
		ady.push_back(&casillas[aux]);
	}
	
	aux = x + (y - 1) * width;
	if ((aux < s - 1) || (aux >= 0)){
		ady.push_back(&casillas[aux]);
	}
	
	aux = x + 1 + (y - 1) * width;
	if ((aux < s - 1) || (aux >= 0)){
		ady.push_back(&casillas[aux]);
	}
	
	aux = x - 1 + y * width;
	if ((aux < s - 1) || (aux >= 0)){
		ady.push_back(&casillas[aux]);
	}
	
	aux = x + 1 + y * width;
	if ((aux < s - 1) || (aux >= 0)){
		ady.push_back(&casillas[aux]);
	}
	
	aux = x - 1 + (y + 1) * width;
	if ((aux < s - 1) || (aux >= 0)){
		ady.push_back(&casillas[aux]);
	}
	
	aux = x + (y + 1) * width;
	if ((aux < s - 1) || (aux >= 0)){
		ady.push_back(&casillas[aux]);
	}
	
	aux = x + 1 + (y + 1) * width;
	if ((aux < s - 1) || (aux >= 0)){
		ady.push_back(&casillas[aux]);
	}
	/*
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
	*/
}

tile gameMap::getTile(int x, int y){
	return casillas[x + y * width];
}

tile* gameMap::getTileP(int x, int y){
	return &casillas[x + y * width];
}

tile* gameMap::getTilePFromUnit(double x, double y){
	double px;
	double py;
	for (px = 0; px < width; px++) {
		if ((px+1)*32 > x) {
			break;
		}
	}
	for (py = 0; py < height; py++) {
		if ((py+1)*32 > y) {
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


void gameMap::setBlocking(std::map<int,unit*> &units){
	for (auto it = units.begin(); it != units.end(); ++it){
		unit *u = it->second;
		int b = u->getBlockingType();
		if (b != B_NOTHING){
			
			std::cout << "unit: " << it->first << std::endl;
			int h = u->getHeight();
			int w = u->getWidth();
			
			int counter_y = (h / TILE_LENGHT);
			if (counter_y < 1) counter_y = 1;
			int counter_x = (w / TILE_LENGHT);
			if (counter_x < 1) counter_x = 1;
			
			std::cout << "casi in y: " << counter_y << std::endl;
			std::cout << "casi in x: " << counter_x << std::endl;
			
			int x_pos = u->getX();
			int y_pos = u->getY();
			
			
			tile *t = this->getTilePFromUnit(x_pos, y_pos);
			int x_tile = t->getX();
			int y_tile = t->getY();
			
			for (int i = x_tile; i < x_tile+counter_x; ++i){
				for (int j = y_tile; j< y_tile+counter_y; ++j){
					tile *t2 = this->getTileP(i,j);
					bool p;
					if (b == B_BLOCK) {
						p = false;
					} else {
						p = true;
					}
					std::cout << "casi que block: " << i << "-" << j << std::endl; 
					t2->putUnitOver(p);
				}
			}
			
		}
	}
}

void gameMap::seePassableForUnit(int unit_code){
	for (auto it = casillas.begin(); it != casillas.end(); ++it){
		std::cout << "x: " << it->getX() << " y: " << it->getY() << " - " << it->isPassable(unit_code) << std::endl;
	}
}
