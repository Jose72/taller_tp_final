#include <stdio.h>
#include <iostream>
#include "gameMap.h"
#include "tile.h"
#include "terrain.h"
#include "pathfinder.h"

int test_astart_solo_tierra();

int main(int argc, char **argv)
{
	test_astart_solo_tierra();
	return 0;
}


int test_astart_solo_tierra(){
	
	//MAPA 4x4 casillas
	
	//seteo casilleros
	//TIERRA, TIERRA, TIERRA, TIERRA
	//TIERRA, TIERRA, TIERRA, TIERRA
	//TIERRA, TIERRA, TIERRA, TIERRA
	//TIERRA, TIERRA, TIERRA, TIERRA
	
	std::vector<tile> casillas;
	tile a(0, 0, TIERRA), b(1, 0, TIERRA), c(2, 0, CARRETERA ), d(3, 0, TIERRA);
	casillas.push_back(a);casillas.push_back(b);casillas.push_back(c);casillas.push_back(d);
	a = tile(0, 1, AGUA); b = tile(1, 1, LAVA); c = tile(2, 1, CARRETERA ); d = tile(3, 1, TIERRA);
	casillas.push_back(a);casillas.push_back(b);casillas.push_back(c);casillas.push_back(d);
	a = tile(0, 2, AGUA); b = tile(1, 2, LAVA); c = tile(2, 2, LAVA); d = tile(3, 2, LAVA);
	casillas.push_back(a);casillas.push_back(b);casillas.push_back(c);casillas.push_back(d);
	a = tile(0, 3, TIERRA); b = tile(1, 3, TIERRA); c = tile(2, 3, TIERRA); d = tile(3, 3, TIERRA);
	casillas.push_back(a);casillas.push_back(b);casillas.push_back(c);casillas.push_back(d);

	/*
	for (auto it = casillas.begin(); it != casillas.end(); ++it){
		it->printTile();
	}
	*/
	
	gameMap mapa(4, 4, casillas);
	
	tile *orig = mapa.getTileP(1,0);
	tile *dest = mapa.getTileP(3,3);
	std::vector<tile*> camino;
	
	
	a_start(orig, dest, mapa, ROBOT, camino);
	std::cout << "camino" << std::endl;
	for (auto it = camino.begin(); it != camino.end(); ++it){
		(*it)->printTile();
	}
	return 0;
}