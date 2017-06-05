#include "testS.h"

#include <stdio.h>
#include <iostream>
#include "gameMap.h"
#include "tile.h"
#include "terrain.h"
#include "actualizeUnit.h"
#include <vector>
#include "unitBuilder.h"
#include "deathHandler.h"

#include <unistd.h>

int flag_capture(){
	int map_codes[100] = {0};
	gameMap mapa(&map_codes[0], 100);
	std::map<int, unit*> units;
	unitBuilder ub;
	int unit_id_count = 6;
	std::set<int> d_units;
	std::set<int> a_units;
	
	unit *r1 = ub.build(GRUNT, 1, 35, 18);
	unit *r2 = ub.build(FLAG, 40, 18);
	unit *r3 = ub.build(FORT, 1, 70, 70);
	unit *r4 = ub.build(GRUNT, 2, 45, 18);
	unit *r5 = ub.build(FORT, 2, 120, 120);
	units.insert(std::pair<int,unit*>(1,r1));
	units.insert(std::pair<int,unit*>(2,r2));
	units.insert(std::pair<int,unit*>(3,r3));
	units.insert(std::pair<int,unit*>(4,r4));
	units.insert(std::pair<int,unit*>(5,r5));

	actualizeUnit au;
	for (int i = 0; i < 460; i++){
		for (auto it = units.begin(); it != units.end(); ++it){
			int id = it->first;
			unit *u = it->second;
			au(id, *u, units, mapa, 200, unit_id_count, d_units, a_units);
		}
		
		if (i == 230) {
			r4->move(90, 18);
		}
		
	}
	
	std::cout << "owner r2: " << r2->getOwner() << std::endl;
	std::cout << "tech_lvl r3: " << r3->getTechLvl() << std::endl;
	std::cout << "tech_lvl r5: " << r5->getTechLvl() << std::endl;
	
	for (auto it = units.begin(); it != units.end(); ++it){
			delete it->second;
		}
	return 0;
}

int test_auto_attack_unit(){
	int map_codes[100] = {0};
	gameMap mapa(&map_codes[0], 100);
	std::map<int, unit*> units;
	unitBuilder ub;
	int unit_id_count = 3;
	std::set<int> d_units;
	std::set<int> a_units;
	
	unit *r1 = ub.build(GRUNT, 1, 35, 18);
	unit *r2 = ub.build(GRUNT, 2, 40, 18);
	units.insert(std::pair<int,unit*>(1,r1));
	units.insert(std::pair<int,unit*>(2,r2));

	actualizeUnit au;
	for (int i = 0; i < 30; i++){
		for (auto it = units.begin(); it != units.end(); ++it){
			int id = it->first;
			unit *u = it->second;
			au(id, *u, units, mapa, 200, unit_id_count, d_units, a_units);
		}
		if (i == 21) {
			std::cout << "-------------------------------" << std::endl;
			r2->move(55,55);
		}
		std::cout << "rel dam r1: " << r1->getRelativeDamage() << std::endl;
		std::cout << "rel dam r2: " << r2->getRelativeDamage() << std::endl;
		//usleep(50000);
	
	}
	for (auto it = units.begin(); it != units.end(); ++it){
			delete it->second;
		}
	return 0;
	
}

int test_create_unit(){
	int map_codes[100] = {0};
	gameMap mapa(&map_codes[0], 100);
	std::map<int, unit*> units;
	unitBuilder ub;
	int unit_id_count = 2;
	std::set<int> d_units;
	std::set<int> a_units;
	
	
	unit *r1 = ub.build(FORT, 1, 35, 18);
	units.insert(std::pair<int,unit*>(1,r1));
	
	int t;
	actualizeUnit au;
	for (int i = 0; i < 3000; i++){
		for (auto it = units.begin(); it != units.end(); ++it){
			int id = it->first;
			unit *u = it->second;
			au(id, *u, units, mapa, 200, unit_id_count, d_units, a_units);
		}
		if (units.size() > 1) {
			t = i;
			break;
		}
		std::cout << "cant u: " << units.size() << std::endl;
		//usleep(50000);
	
	}
	
	std::cout << "t: " << t << std::endl;
	
	for (auto it = units.begin(); it != units.end(); ++it){
			delete it->second;
		}

	return 0;
	
}





int test_death_of_target(){
	
int map_codes[100] = {0};
	gameMap mapa(&map_codes[0], 100);
	std::map<int, unit*> units;
	unitBuilder ub;
	deathHandler dh;
	int unit_id_count = 3;
	std::set<int> d_units;
	std::set<int> a_units;
	
	
	unit *r1 = ub.build(GRUNT, 1, 35, 18);
	unit *r2 = ub.build(GRUNT, 2, 40, 18);
	
	units.insert(std::pair<int,unit*>(1,r1));
	units.insert(std::pair<int,unit*>(2,r2));
	r1->attack(r2);
	
	actualizeUnit au;
	for (int i = 0; i < 100; i++){
		for (auto it = units.begin(); it != units.end(); ++it){
			int id = it->first;
			unit *u = it->second;
			au(id, *u, units, mapa, 200, unit_id_count, d_units, a_units);
		}
		
		//limpio los fiambres
		for (auto it = units.begin(); it != units.end(); ){
			unit *u = it->second;
			if (u->isDead()) {
				dh.death(*u, units);
				it = units.erase(it);
			} else {
				++it;
			}
		}
		
		//au(1, r1, units, mapa, 1, unit_id_count, d_units, a_units);
		//au(1, *r2, units, mapa, 1, unit_id_count, d_units, a_units);
		std::cout << "cant u: " << units.size() << std::endl;
		std::cout << "daño rel r2: " << r2->getRelativeDamage() << std::endl;
		usleep(50000);
	
	}
	
	delete r2;
	delete r1;

	return 0;
}




int test_bullet_attack(){
	int map_codes[100] = {0};
	gameMap mapa(&map_codes[0], 100);
	std::map<int, unit*> units;
	unitBuilder ub;
	deathHandler dh;
	int unit_id_count = 3;
	std::set<int> d_units;
	std::set<int> a_units;
	
	
	unit *r1 = ub.build(GRUNT, 1, 35, 18);
	unit *r2 = ub.build(GRUNT, 2, 40, 18);
	
	units.insert(std::pair<int,unit*>(1,r1));
	units.insert(std::pair<int,unit*>(2,r2));
	r1->attack(r2);
	
	actualizeUnit au;
	for (int i = 0; i < 27; i++){
		for (auto it = units.begin(); it != units.end(); ++it){
			int id = it->first;
			unit *u = it->second;
			au(id, *u, units, mapa, 200, unit_id_count, d_units, a_units);
		}
		
		//limpio los fiambres
		for (auto it = units.begin(); it != units.end(); ){
			unit *u = it->second;
			if (u->isDead()) {
				dh.death(*u, units);
				it = units.erase(it);
			} else {
				++it;
			}
		}
		
		//au(1, r1, units, mapa, 1, unit_id_count, d_units, a_units);
		//au(1, *r2, units, mapa, 1, unit_id_count, d_units, a_units);
		std::cout << "cant u: " << units.size() << std::endl;
		std::cout << "daño rel r2: " << r2->getRelativeDamage() << std::endl;
		usleep(200000);
	
	}
	
	delete r2;
	delete r1;

	return 0;
}



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