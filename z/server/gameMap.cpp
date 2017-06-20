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
	//this->setHighResMap();
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
	//this->setHighResMap();
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


////////////////////////////////////////////////777
///////////////////////////////////////////////////7
/////////////////////////////////////////////////////77
// NO SE SI SE VA A USAR
////////////////////////////////////////////////////
void gameMap::setHighResMap(){
	//std::vector<tile> h_casillas;
	for (int i = 0; i < (height * 2); ++i){
		for (int j = 0; j < (width * 2); ++j){
			tile t(i,j,0);
			h_casillas.push_back(t);
		}
	}
	for (int i = 0; i < height; ++i){
		for (int j = 0; j < width; ++j){
			tile c = casillas[j + i * width];
			//std::cout << "CASS------------------- " << std::endl;
			int t_code = c.getTerrainCode();
			//std::cout << "casilla" << " x: " << i << " y: " << j << std::endl;
			(&h_casillas[(j * 2) + (i * 2) * width * 2])->setTerrain(t_code);
			//std::cout << "subcasilla" << " x: " << i*2 << " y: " << j*2 << std::endl;
			(&h_casillas[(j * 2 + 1) + (i * 2) * width * 2])->setTerrain(t_code);
			//std::cout << "subcasilla" << " x: " << i*2+1 << " y: " << j*2 << std::endl;
			(&h_casillas[(j * 2) + (i * 2 + 1) * width * 2])->setTerrain(t_code);
			//std::cout << "subcasilla" << " x: " << i*2 << " y: " << j*2+1 << std::endl;
			(&h_casillas[(j * 2 + 1) + (i * 2 + 1) * width * 2])->setTerrain(t_code);
			//std::cout << "subcasilla" << " x: " << i*2+1 << " y: " << j*2+1 << std::endl;
		}
	}
	for (unsigned int i = 0; i < h_casillas.size(); i++){
		h_casillas[i].printTile();
	}

}

void gameMap::getNeightboorsHRes(tile &q, std::vector<tile*> &ady){
	//tomo el x,y de la casilla
	int x = q.getX();
	int y = q.getY();

	for (int dx = -1; dx < 2; dx++){
		for (int dy = -1; dy < 2; dy++){
			int new_x = x + dx;
			int new_y = y + dy;
		    int pos = new_x + new_y * width*2; //width tendria que ser cant de casillas horizontal
			//si x e y son positivos, y no se pasan de cant de casillas, y la pos existe
			if (new_x >= 0 && new_y >= 0 && pos < (int) h_casillas.size() &&
			!(new_x == x && new_y == y) && (new_x < width*2) && (new_y < height*2)) {
				//la guardo
				ady.push_back(&h_casillas[pos]);
			}
		}
	}
	
}

void gameMap::setBlockingHRes(std::map<int,unit*> &units){
	for (auto it = units.begin(); it != units.end(); ++it){
		unit *u = it->second;
		int b = u->getBlockingType();
		if (b != B_NOTHING){
			
			std::cout << "unit: " << it->first << std::endl;
			int h = u->getHeight();
			int w = u->getWidth();
			
			int counter_y = (h / 16);
			if (counter_y < 1) counter_y = 1;
			int counter_x = (w / 16);
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
					//std::cout << "casi que block: " << i << "-" << j << std::endl; 
					t2->putUnitOver(p);
				}
			}
			
		}
	}
}

tile gameMap::getTileHRes(int x, int y){
	return h_casillas[x + y * width*2];
}

tile* gameMap::getTilePHRes(int x, int y){
	return &h_casillas[x + y * width*2];
}

tile* gameMap::getTilePFromUnitHRes(double x, double y){
	double px;
	double py;
	for (px = 0; px < width*2; px++) {
		if ((px+1)*16 > x) {
			break;
		}
	}
	for (py = 0; py < height*2; py++) {
		if ((py+1)*16 > y) {
			break;
		}
	}
	std::cout << "px: " << px << " py: "<< py << std::endl;
	return &h_casillas[px + py * width*2];
};

