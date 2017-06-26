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

int gameMap::getMapDimension(){
	return height;
}

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


void gameMap::getNeightboorsNoDiagonal(tile &q, std::vector<tile*> &ady){
	this->getNeightboors(q, ady);
	for (auto it = ady.begin(); it != ady.end(); ++it){
		if ((*it)->isDiagonal(q)){
			it = ady.erase(it);
		}
	}
}


//puntero a la casilla con las coordenadas indicadas
tile* gameMap::getTileP(int x, int y){
	return &casillas[x + y * width];
}

//puntero a la casilla donde se encuentra la unidad con las coordenadas indicadas
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


//imprime las casilla (para testing)
void gameMap::printMap(){
	for (unsigned int i = 0; i < casillas.size(); i++){
		casillas[i].printTile();
	}
}

//recibe el mapa de unidades, y bloquea o "desbloquea"
//las casillas correspondientes
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
			
			//std::cout << "casi in y: " << counter_y << std::endl;
			//std::cout << "casi in x: " << counter_x << std::endl;
			
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
					//std::cout << "casi que block: " << i << "-" << j << std::endl; 
					t2->putUnitOver(p);
				}
			}
			
		}
	}
}

//para testing
void gameMap::seePassableForUnit(int unit_code){
	for (auto it = casillas.begin(); it != casillas.end(); ++it){
		std::cout << "x: " << it->getX() << " y: " << it->getY() << " - " << it->isPassable(unit_code) << std::endl;
	}
}


//bloquea la/las casillas que ocupa la unidad
//(ej: cuando se destruye un puente)
void gameMap::setUnitAsBlocking(unit *u){
	int h = u->getHeight();
	int w = u->getWidth();
			
	int counter_y = (h / TILE_LENGHT);
	if (counter_y < 1) counter_y = 1;
	int counter_x = (w / TILE_LENGHT);
	if (counter_x < 1) counter_x = 1;
			
	int x_pos = u->getX();
	int y_pos = u->getY();
			
	tile *t = this->getTilePFromUnit(x_pos, y_pos);
	int x_tile = t->getX();
	int y_tile = t->getY();
			
	for (int i = x_tile; i < x_tile+counter_x; ++i){
		for (int j = y_tile; j< y_tile+counter_y; ++j){
			tile *t2 = this->getTileP(i,j);
			bool p = false;
			t2->putUnitOver(p);
		}
	}
}

//si la unidad esta en una casilla en la que no podria (esta bloqueada)
bool gameMap::impossibleTile(int x, int y, int class_u){
	tile *t = getTilePFromUnit(x, y);
	return !t->isPassable(class_u);
}

void gameMap::releaseUnitBlocking(unit *u){
	int h = u->getHeight();
	int w = u->getWidth();
			
	int counter_y = (h / TILE_LENGHT);
	if (counter_y < 1) counter_y = 1;
	int counter_x = (w / TILE_LENGHT);
	if (counter_x < 1) counter_x = 1;
			
	int x_pos = u->getX();
	int y_pos = u->getY();
			
	tile *t = this->getTilePFromUnit(x_pos, y_pos);
	int x_tile = t->getX();
	int y_tile = t->getY();
			
	for (int i = x_tile; i < x_tile+counter_x; ++i){
		for (int j = y_tile; j< y_tile+counter_y; ++j){
			tile *t2 = this->getTileP(i,j);
			t2->releaseUnitOver();
		}
	}
}

tile* gameMap::getClosestPassableTile(int x, int y, int c_unit){
	tile *dest = this->getTileP(x,y);
	tile *t = nullptr;
	int dist = width*height*32;
	for (auto it = casillas.begin(); it != casillas.end(); ++it){
		if (dist > dest->euclideanDist(&(*it)) && (dest != &(*it)) && (*it).isPassable(c_unit)){
			dist = dest->euclideanDist(&(*it));
			t = &(*it);
		}
	}
	return t;
}
