#include "testS.h"

#include <stdio.h>
#include <iostream>
#include "gameMap.h"
#include "tile.h"
#include "terrain.h"
#include "actualizeUnit.h"
#include <vector>

int test_create_map(){
	std::vector<int> tile_codes;
	int map_codes[100] = {0};
	map_codes[15] = 1;
	map_codes[16] = 1;
	map_codes[17] = 1;
	map_codes[18] = 1;
	map_codes[31] = 1;
	map_codes[32] = 1;
	map_codes[33] = 1;
	map_codes[34] = 1;
	map_codes[56] = 2;
	map_codes[57] = 2;
	map_codes[58] = 2;
	for (int i = 0; i < 100; i++){
		tile_codes.push_back(map_codes[i]);
	}
	gameMap mapa(tile_codes);
	std::cout << "mam" << std::endl;
	mapa.printMap();
	return 0;
}

int test_attack_unit_in_range(){
	unit r1(ROBOT, GRUNT, 35, 18, 300, ROBOT_SPEED);
	unit r2(ROBOT, GRUNT, 40, 18, 300, ROBOT_SPEED);
	unit r4(ROBOT, GRUNT, 43, 18, 300, ROBOT_SPEED);
	return 0;
}


int test_units_in_range(){
	unit r1(ROBOT, GRUNT, 35, 18, 300, ROBOT_SPEED);
	unit r2(ROBOT, GRUNT, 40, 18, 300, ROBOT_SPEED);
	unit r3(ROBOT, GRUNT, 42, 18, 300, ROBOT_SPEED);
	unit r4(ROBOT, GRUNT, 43, 18, 300, ROBOT_SPEED);
	unit r5(ROBOT, GRUNT, 35, 22, 300, ROBOT_SPEED);
	std::cout << r1.isInRange(r2, 7) << std::endl;
	std::cout << r1.isInRange(r3, 7) << std::endl;
	std::cout << r1.isInRange(r4, 7) << std::endl;
	std::cout << r1.isInRange(r5, 7) << std::endl;
	return 0;
}

int test_move_unit(){
	actualizeUnit au;
	std::vector<tile> casillas;
	tile a(0, 0, TIERRA), b(1, 0, AGUA), c(2, 0, TIERRA), d(3, 0, TIERRA);
	casillas.push_back(a);casillas.push_back(b);casillas.push_back(c);casillas.push_back(d);
	a = tile(0, 1, TIERRA); b = tile(1, 1, AGUA); c = tile(2, 1, AGUA ); d = tile(3, 1, TIERRA);
	casillas.push_back(a);casillas.push_back(b);casillas.push_back(c);casillas.push_back(d);
	a = tile(0, 2, TIERRA); b = tile(1, 2, TIERRA); c = tile(2, 2, TIERRA); d = tile(3, 2, TIERRA);
	casillas.push_back(a);casillas.push_back(b);casillas.push_back(c);casillas.push_back(d);
	a = tile(0, 3, TIERRA); b = tile(1, 3, TIERRA); c = tile(2, 3, TIERRA); d = tile(3, 3, TIERRA);
	casillas.push_back(a);casillas.push_back(b);casillas.push_back(c);casillas.push_back(d);
	
	gameMap mapa(4, 4, casillas);
	// x from 0 to 127
	// y from 0 to 127
	
	//unit in (1,0), in  (35, 18)
	// to (2,2), in (80, 70)
	// to (3,3), in (108, 112)
	
	unit r(ROBOT, GRUNT, 35, 18, 300, ROBOT_SPEED);
	r.move(108, 112);
	
	while (r.isMoving()){
		au(r, mapa, 1);
	}
	
	return 0;
}


int test_find_unit_tile(){
	
	std::vector<tile> casillas;
	tile a(0, 0, TIERRA), b(1, 0, TIERRA), c(2, 0, LAVA ), d(3, 0, TIERRA);
	casillas.push_back(a);casillas.push_back(b);casillas.push_back(c);casillas.push_back(d);
	a = tile(0, 1, TIERRA); b = tile(1, 1, LAVA); c = tile(2, 1, TIERRA ); d = tile(3, 1, TIERRA);
	casillas.push_back(a);casillas.push_back(b);casillas.push_back(c);casillas.push_back(d);
	a = tile(0, 2, TIERRA); b = tile(1, 2, LAVA); c = tile(2, 2, TIERRA); d = tile(3, 2, TIERRA);
	casillas.push_back(a);casillas.push_back(b);casillas.push_back(c);casillas.push_back(d);
	a = tile(0, 3, TIERRA); b = tile(1, 3, TIERRA); c = tile(2, 3, TIERRA); d = tile(3, 3, TIERRA);
	casillas.push_back(a);casillas.push_back(b);casillas.push_back(c);casillas.push_back(d);
	
	gameMap mapa(4, 4, casillas);
	// x from 0 to 127
	// y from 0 to 127
	
	//unit in (1,0), in  (35, 18)
	// to (2,2), in (80, 70)
	tile *oo = mapa.getTilePFromUnit(35, 18);
	tile *de = mapa.getTilePFromUnit(80, 70);
	
	oo->printTile();
	de->printTile();
	
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
	tile a(0, 0, TIERRA), b(1, 0, TIERRA), c(2, 0, LAVA ), d(3, 0, TIERRA);
	casillas.push_back(a);casillas.push_back(b);casillas.push_back(c);casillas.push_back(d);
	a = tile(0, 1, TIERRA); b = tile(1, 1, LAVA); c = tile(2, 1, TIERRA ); d = tile(3, 1, TIERRA);
	casillas.push_back(a);casillas.push_back(b);casillas.push_back(c);casillas.push_back(d);
	a = tile(0, 2, TIERRA); b = tile(1, 2, LAVA); c = tile(2, 2, TIERRA); d = tile(3, 2, TIERRA);
	casillas.push_back(a);casillas.push_back(b);casillas.push_back(c);casillas.push_back(d);
	a = tile(0, 3, TIERRA); b = tile(1, 3, TIERRA); c = tile(2, 3, TIERRA); d = tile(3, 3, TIERRA);
	casillas.push_back(a);casillas.push_back(b);casillas.push_back(c);casillas.push_back(d);

	/*
	for (auto it = casillas.begin(); it != casillas.end(); ++it){
		it->printTile();
	}
	*/
	
	gameMap mapa(4, 4, casillas);
	
	tile *orig = mapa.getTileP(0,0);
	tile *dest = mapa.getTileP(3,3);
	std::vector<tile*> camino;
	
	
	aStart(orig, dest, mapa, ROBOT, camino);
	std::cout << "camino" << std::endl;
	for (auto it = camino.begin(); it != camino.end(); ++it){
		(*it)->printTile();
	}
	return 0;
}