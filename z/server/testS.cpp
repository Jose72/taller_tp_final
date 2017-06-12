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
#include "infoPlayer.h"

#include <unistd.h>

int test_create_units(){
	int map_codes[100] = {0};
	gameMap mapa(&map_codes[0], 100);
	std::map<int, unit*> units;
	unitBuilder ub;
	infoPlayers p_info(4, DEATHMATCH, 0);
	int unit_id_count = 4;
	std::set<int> d_units;
	std::set<int> a_units;
	
	//se le murio el fuerte
	unit *r1 = ub.build(FORT, 1, 40, 40);
	unit *r2 = ub.build(VEHICLE_FACTORY, 1, 145, 150);
	unit *r3 = ub.build(ROBOT_FACTORY, 1, 177, 100);
	
	units.insert(std::pair<int,unit*>(1,r1));
	units.insert(std::pair<int,unit*>(2,r2));
	units.insert(std::pair<int,unit*>(3,r3));

	r1->create(PYRO, 5000);
	r2->create(MML, 5000);
	r3->create(LAZER, 5000);
	
	actualizeUnit au;
	for (int i = 0; i < 30; i++){
		for (auto it = units.begin(); it != units.end(); ++it){
			int id = it->first;
			unit *u = it->second;
			std::cout << "unit: " << id << " type: " << u->getUnitId() << std::endl;
			au(id, *u, units, mapa, 200, unit_id_count, p_info);
		}
	}
	
	for (auto it = units.begin(); it != units.end(); ++it){
			delete it->second;
		}

	return 0;
}

int test_info_players(){
	int map_codes[100] = {0};
	gameMap mapa(&map_codes[0], 100);
	std::map<int, unit*> units;
	unitBuilder ub;
	infoPlayers p_info(4, DEATHMATCH, 0);
	deathHandler death_h;
	int unit_id_count = 9;
	std::set<int> d_units;
	std::set<int> a_units;
	
	
	infoPlayers ip(2,DEATHMATCH,0);
	ip.addNewPlayer(1);
	ip.addNewPlayer(2);
	/*
	//se le murieron tdas la unidades
	unit *r1 = ub.build(FORT, 1, 40, 40);
	unit *r2 = ub.build(GRUNT, 1, 70, 40);
	unit *r3 = ub.build(GRUNT, 1, 77, 40);
	unit *r4 = ub.build(GRUNT, 1, 84, 30);
	unit *r5 = ub.build(FORT, 2, 160, 160);
	unit *r6 = ub.build(GRUNT, 2, 70, 55);
	unit *r7 = ub.build(GRUNT, 2, 77, 55);
	unit *r8 = ub.build(GRUNT, 2, 84, 55);
	*/
	
	//se le murio el fuerte
	unit *r1 = ub.build(FORT, 1, 40, 40);
	unit *r2 = ub.build(TOUGHT, 1, 145, 150);
	unit *r3 = ub.build(TOUGHT, 1, 150, 150);
	unit *r4 = ub.build(TOUGHT, 1, 140, 150);
	
	unit *r5 = ub.build(FORT, 2, 160, 160);
	unit *r6 = ub.build(PYRO, 2, 50, 50);
	unit *r7 = ub.build(PYRO, 2, 55, 50);
	unit *r8 = ub.build(PYRO, 2, 45, 50);
	
	ip.initializePlayer(1, r1, 3);
	ip.initializePlayer(2, r5, 3);
	
	units.insert(std::pair<int,unit*>(1,r1));
	units.insert(std::pair<int,unit*>(2,r2));
	units.insert(std::pair<int,unit*>(3,r3));
	units.insert(std::pair<int,unit*>(4,r4));
	units.insert(std::pair<int,unit*>(5,r5));
	units.insert(std::pair<int,unit*>(6,r6));
	units.insert(std::pair<int,unit*>(7,r7));
	units.insert(std::pair<int,unit*>(8,r8));

	
	actualizeUnit au;
	for (int i = 0; i < 47; i++){
		for (auto it = units.begin(); it != units.end(); ++it){
			int id = it->first;
			unit *u = it->second;
			au(id, *u, units, mapa, 200, unit_id_count, p_info);
		}
		//std::cout << "units clean " << std::endl;
		for (auto it = units.begin(); it != units.end(); ){
			unit *u = it->second;
			if (u->isDead()) {
				death_h.death(*u, units);//handler por si tiene q hacer algo
				ip.decrementUnitsCount(u->getOwner());
				std::cout << "unit " << it->first << " dead" << std::endl;
				delete it->second; // libero mem
				it = units.erase(it); // borro de la lista
			} else {
				++it;
			}
		}
		
		if (DEFEAT == ip.updateVictoryConditions(1)){
			for (auto it = units.begin(); it != units.end(); ++it){
				unit *u = it->second;
				if (u->getOwner() == 1){
					u->changeState(DEFEATED);
				}
			}
		}
		
		if (DEFEAT == ip.updateVictoryConditions(2)){
			for (auto it = units.begin(); it != units.end(); ++it){
				unit *u = it->second;
				if (u->getOwner() == 2){
					u->changeState(DEFEATED);
				}
			}
			
		}
		
	}
	
	std::cout << "rel dam r1: " << r1->getRelativeDamage() << std::endl;
	std::cout << "rel dam r2: " << r2->getRelativeDamage() << std::endl;
	std::cout << "rel dam r3: " << r3->getRelativeDamage() << std::endl;
	std::cout << "rel dam r4: " << r4->getRelativeDamage() << std::endl;
	std::cout << "rel dam r5: " << r5->getRelativeDamage() << std::endl;
	std::cout << "rel dam r6: " << r6->getRelativeDamage() << std::endl;
	std::cout << "rel dam r7: " << r7->getRelativeDamage() << std::endl;
	std::cout << "rel dam r8: " << r8->getRelativeDamage() << std::endl;
	
	
	for (auto it = units.begin(); it != units.end(); ++it){
			delete it->second;
		}
	
	//std::cout << "rel dam r8: " << r8->getRelativeDamage() << std::endl;
	//std::cout << "rel dam r8: " << r8->getRelativeDamage() << std::endl;
	
	return 0;
	return 0;
}

int test_unit_driving(){
	int map_codes[100] = {0};
	gameMap mapa(&map_codes[0], 100);
	std::map<int, unit*> units;
	unitBuilder ub;
	infoPlayers p_info(4, DEATHMATCH, 0);
	int unit_id_count = 4;
	std::set<int> d_units;
	std::set<int> a_units;
	
	unit *r1 = ub.build(GRUNT, 1, 27, 18);
	unit *r2 = ub.build(JEEP, 1, 45, 18);
	unit *r3 = ub.build(GRUNT, 2, 37, 18);
	units.insert(std::pair<int,unit*>(1,r1));
	units.insert(std::pair<int,unit*>(2,r2));
	
	units.insert(std::pair<int,unit*>(3,r3));
	
	r1->drive(r2);
	r3->attack(r1);
	
	actualizeUnit au;
	for (int i = 0; i < 10; i++){
		for (auto it = units.begin(); it != units.end(); ++it){
			int id = it->first;
			unit *u = it->second;
			au(id, *u, units, mapa, 200, unit_id_count, p_info);
		}
	}
	
	std::cout << "rel dam r1: " << r1->getRelativeDamage() << std::endl;
	std::cout << "rel dam r2: " << r2->getRelativeDamage() << std::endl;
	std::cout << "rel dam r3: " << r3->getRelativeDamage() << std::endl;
	
	for (auto it = units.begin(); it != units.end(); ++it){
			delete it->second;
		}
	return 0;
}

int flag_capture(){
	int map_codes[100] = {0};
	gameMap mapa(&map_codes[0], 100);
	std::map<int, unit*> units;
	unitBuilder ub;
	int unit_id_count = 6;
	infoPlayers p_info(4, DEATHMATCH, 0);
	
	
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
	p_info.addNewPlayer(1);
	p_info.initializePlayer(1, r3,2);
	p_info.addNewPlayer(2);
	p_info.initializePlayer(2, r5,2);


	actualizeUnit au;
	for (int i = 0; i < 100; i++){
		for (auto it = units.begin(); it != units.end(); ++it){
			int id = it->first;
			unit *u = it->second;
			au(id, *u, units, mapa, 200, unit_id_count, p_info);
		}
		if (i == 50) {
			r4->move(200,200);
			/*
			std::map<int,unit*>::iterator it;
			it = units.find(4);
			(it->second)->stopFollowers();
			units.erase(4);
			*/
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
	infoPlayers p_info(4, DEATHMATCH, 0);
	
	unit *r1 = ub.build(GRUNT, 1, 37, 18);
	unit *r2 = ub.build(GRUNT, 2, 40, 18);
	units.insert(std::pair<int,unit*>(1,r1));
	units.insert(std::pair<int,unit*>(2,r2));

	actualizeUnit au;
	for (int i = 0; i < 35; i++){
		for (auto it = units.begin(); it != units.end(); ++it){
			int id = it->first;
			unit *u = it->second;
			au(id, *u, units, mapa, 200, unit_id_count, p_info);
		}
		if (i == 21) {
			std::cout << "-------------------------------" << std::endl;
			//r2->move(55,55);
		}
		std::cout << "rel dam r1: " << r1->getRelativeDamage() << std::endl;
		std::cout << "rel dam r2: " << r2->getRelativeDamage() << std::endl;
		
		std::cout << "targetr1: " << r1->getTarget() << std::endl;
		//usleep(50000);
		for (auto it = units.begin(); it != units.end(); ){
			unit *u = it->second;
			if (u->isDead()) {
				delete it->second; // libero mem
				it = units.erase(it); // borro de la lista
				std::cout << "reased----------" << std::endl;
			} else {
				++it;
			}
		}
	
	}
	
	
	return 0;
	
}

int test_create_unit(){
	int map_codes[100] = {0};
	gameMap mapa(&map_codes[0], 100);
	std::map<int, unit*> units;
	unitBuilder ub;
	int unit_id_count = 2;
	infoPlayers p_info(4, DEATHMATCH, 0);
	
	
	unit *r1 = ub.build(FORT, 1, 35, 18);
	units.insert(std::pair<int,unit*>(1,r1));
	
	int t;
	actualizeUnit au;
	for (int i = 0; i < 3000; i++){
		for (auto it = units.begin(); it != units.end(); ++it){
			int id = it->first;
			unit *u = it->second;
			au(id, *u, units, mapa, 200, unit_id_count, p_info);
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
	infoPlayers p_info(4, DEATHMATCH, 0);
	
	
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
			au(id, *u, units, mapa, 200, unit_id_count, p_info);
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
	infoPlayers p_info(4, DEATHMATCH, 0);
	
	
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
			au(id, *u, units, mapa, 200, unit_id_count, p_info);
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
	infoPlayers p_info(4, DEATHMATCH, 0);
	
	unit r1(1, GRUNT, 35, 18);
	unit *r2 = ub.build(MISIL, 60, 60);
	actualizeUnit au;
	units.insert(std::pair<int,unit*>(1,&r1));
	
	r1.move(55, 67);
	r2->move(123, 123);
	for (int i = 0; i < 27; i++){
		//au(1, r1, units, mapa, 1, unit_id_count, d_units, a_units);
		au(1, *r2, units, mapa, 1, unit_id_count, p_info);
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

