#include "testS.h"

#include <stdio.h>
#include <iostream>
#include "gameMap.h"
#include "tile.h"
#include "terrain.h"
#include "actualizeUnit.h"
#include <vector>
#include "unitBuilder.h"

#include <unistd.h>
/*
int test_create_unit(){
	int map_codes[100] = {0};
	gameMap mapa(&map_codes[0], 100);
	std::map<int, unit*> units;
	int unit_id_count = 1;
	
	unit *r1 = new unit(1, ROBOT_FACTORY, 35, 18);
	units.insert(std::pair<int,unit*>(unit_id_count,r1));
	unit_id_count++;
	
	actualizeUnit au;
	for (int i = 0; i < 1200; i++){
		au(*r1, units, mapa, 1, unit_id_count);
		
	}
	std::cout << units.size() << std::endl;
	
	for (auto it = units.begin(); it != units.end(); ++it){
		unit* h = it->second;
		std::cout << "owner: " << h->getOwner() << std::endl;
		std::cout << "unit id: " << h->getUnitId() << std::endl;
		delete it->second;
	}
	
	return 0;
}


int test_auto_attack_unit(){
	int map_codes[100] = {0};
	gameMap mapa(&map_codes[0], 100);
	std::map<int, unit*> units;
	int unit_id_count = 1;
	
	unit r1(1, GRUNT, 35, 18);
	unit r2(2, GRUNT, 40, 18);
	unit r3(3, GRUNT, 60, 18);
	actualizeUnit au;
	units.insert(std::pair<int,unit*>(1,&r1));
	units.insert(std::pair<int,unit*>(2,&r2));
	units.insert(std::pair<int,unit*>(3,&r3));
	
	r1.move(44, 22);
	r3.setAttack(&r2);
	for (int i = 0; i < 27; i++){
		au(r1, units, mapa, 1, unit_id_count);
		au(r2, units, mapa, 1, unit_id_count);
		au(r3, units, mapa, 1, unit_id_count);
		
		std::cout << "daño rel r1: " << r1.getRelativeDamage() << std::endl;
		std::cout << "daño rel r2: " << r2.getRelativeDamage() << std::endl;
		std::cout << "daño rel r3: " << r3.getRelativeDamage() << std::endl;
	}

	
	return 0;
	
}


int test_attack_unit_in_range(){
	int map_codes[100] = {0};
	gameMap mapa(&map_codes[0], 100);
	std::map<int, unit*> units;
	int unit_id_count = 1;
	
	unit r1(1,GRUNT, 35, 18);
	unit r2(2,GRUNT, 40, 18);
	unit r4(3,GRUNT, 35, 18);
	unit r5(4,JEEP, 44, 18);
	actualizeUnit au;
	std::cout << "daño rel r2: " << r2.getRelativeDamage() << std::endl;
	r1.setAttack(&r2);
	au(r1, units, mapa, 1, unit_id_count);
	std::cout << "daño rel r2: " << r2.getRelativeDamage() << std::endl;
	
	
	r5.setAttack(&r4);
	
	r4.move(100, 18);
	
	for (int i = 0; i < 27; i++){
		au(r4, units,mapa, 1, unit_id_count);
		au(r5, units,mapa, 1, unit_id_count);
		
		std::cout << "daño rel r4: " << r4.getRelativeDamage() << std::endl;
	}

	
	return 0;
	
}

int test_create_map(){
	
	actualizeUnit au;
	std::vector<int> tile_codes;
	std::map<int, unit*> units;
	int map_codes[100] = {0};
	int unit_id_count = 1;
	
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
	
	
	unit r(1, GRUNT, 200, 10);
	r.move(200, 200);
	
	while (r.isMoving()){
		au(r, units,mapa, 1, unit_id_count);
	}
	
	return 0;
}




int test_bullet_attack(){
	unit r1(1, GRUNT, 35, 18);
	unit r2(2, GRUNT, 40, 18);
	unit r3(3, GRUNT, 42, 18);
	unit r4(4, GRUNT, 43, 18);
	unit r5(5, GRUNT, 35, 22);
	std::cout << r1.isInRange(r2) << std::endl;
	std::cout << r1.isInRange(r3) << std::endl;
	std::cout << r1.isInRange(r4) << std::endl;
	std::cout << r1.isInRange(r5) << std::endl;
	return 0;
}
*/


int test_move_unit(){
	int map_codes[100] = {0};
	gameMap mapa(&map_codes[0], 100);
	std::map<int, unit*> units;
	unitBuilder ub;
	int unit_id_count = 1;
	std::set<int> d_units;
	std::set<int> a_units;
	
	unit r1(1, GRUNT, 35, 18);
	unit *r2 = ub.build(MISIL, 60, 60);
	actualizeUnit au;
	units.insert(std::pair<int,unit*>(1,&r1));
	
	r1.move(55, 67);
	r2->move(123, 123);
	for (int i = 0; i < 27; i++){
		//au(1, r1, units, mapa, 1, unit_id_count, d_units, a_units);
		au(1, *r2, units, mapa, 1, unit_id_count, d_units, a_units);
		usleep(200000);
	
	}
	delete r2;
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