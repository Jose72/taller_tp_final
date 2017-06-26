
#include "infoUnits.h"
#include <iostream>
#include "JsonUnitInfoHandler.h"

unitPlantilla::unitPlantilla(int unit_c, int class_c, int height, int width, 
int health, int blocking, int speed, int range_u, int damage, bool explosive, 
int fab_time, int shoot_time, int unit_to_c, int tech_lvl, int q_to_fab): 
unit_c(unit_c), class_c(class_c), height(height), width(width), 
health(health), blocking(blocking), speed(speed), range_u(range_u), 
damage(damage), explosive(explosive), unit_to_create(unit_to_c), 
fab_time(fab_time), shoot_time(shoot_time), tech_lvl(tech_lvl), 
quant_fab(q_to_fab){}

int unitPlantilla::getUnitCode(){
	return unit_c;
}

int unitPlantilla::getClassCode(){
	return class_c;
}

int unitPlantilla::getHeight(){
	return height;
}

int unitPlantilla::getWidth(){
	return width;
}

int unitPlantilla::getHealth(){
	return health;
}

int unitPlantilla::getBlocking(){
	return blocking;
}

int unitPlantilla::getSpeed(){
	return speed;
}

int unitPlantilla::getRange(){
	return range_u;
}

int unitPlantilla::getDamage(){
	return damage;
}

bool unitPlantilla::getExplosive(){
	return explosive;
}

int unitPlantilla::getUnitToCreate(){
	return unit_to_create;
}

int unitPlantilla::getFabTime(){
	return fab_time;
}

int unitPlantilla::getShootTime(){
	return shoot_time;
}

int unitPlantilla::getTechLvl(){
	return tech_lvl;
}

int unitPlantilla::getQuantToFab(){
	return quant_fab;
}

void unitPlantilla::print(){
	std::cout <<
	"unit_c: " << unit_c << "\n" << 
	" class_c: " << class_c << "\n" << 
	" height: " << height << "\n" << 
	" width: " << width << "\n" << 
	" health: " << health << "\n" << 
	" blocking: " << blocking << "\n" << 
	" speed: " << speed << "\n" << 
	" range: " << range_u << "\n" << 
	" damage: " << damage << "\n" << 
	" explosive: " << explosive << "\n" << 
	" unit_to_create: " << unit_to_create << "\n" << 
	" fab_time: " << fab_time << "\n" << 
	" shoot_time: " << shoot_time << "\n" << 
	" tech_lvl: " << tech_lvl << "\n" << 
	" quant_fab: " << quant_fab <<
	std::endl;
}

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
infoUnits::infoUnits(std::string &file_path){
	JsonUnitInfoHandler ju;
	ju.jsonToUnitsInfo(file_path, *this);
	//u_info.print();
}

void infoUnits::addInfo(unitPlantilla &up){
	plantillas.push_back(up);
}

int infoUnits::getClassCode(int unit_c){
	for (auto it = plantillas.begin(); it != plantillas.end(); ++it){
		if (it->getUnitCode() == unit_c){
			return it->getClassCode();
		}
	}
	return -1;
}

int infoUnits::getHeight(int unit_c){
	for (auto it = plantillas.begin(); it != plantillas.end(); ++it){
		if (it->getUnitCode() == unit_c){
			return it->getHeight();
		}
	}
	return -1;
}

int infoUnits::getWidth(int unit_c){
	for (auto it = plantillas.begin(); it != plantillas.end(); ++it){
		if (it->getUnitCode() == unit_c){
			return it->getWidth();
		}
	}
	return -1;
}

int infoUnits::getHealth(int unit_c){
	for (auto it = plantillas.begin(); it != plantillas.end(); ++it){
		if (it->getUnitCode() == unit_c){
			return it->getHealth();
		}
	}
	return -1;
}

int infoUnits::getBlocking(int unit_c){
	for (auto it = plantillas.begin(); it != plantillas.end(); ++it){
		if (it->getUnitCode() == unit_c){
			return it->getBlocking();
		}
	}
	return -1;
}

int infoUnits::getSpeed(int unit_c){
	for (auto it = plantillas.begin(); it != plantillas.end(); ++it){
		if (it->getUnitCode() == unit_c){
			return it->getSpeed();
		}
	}
	return -1;
}

int infoUnits::getRange(int unit_c){
	for (auto it = plantillas.begin(); it != plantillas.end(); ++it){
		if (it->getUnitCode() == unit_c){
			return it->getRange();
		}
	}
	return -1;
}

int infoUnits::getDamage(int unit_c){
	for (auto it = plantillas.begin(); it != plantillas.end(); ++it){
		if (it->getUnitCode() == unit_c){
			return it->getDamage();
		}
	}
	return -1;
}

bool infoUnits::getExplosive(int unit_c){
	for (auto it = plantillas.begin(); it != plantillas.end(); ++it){
		if (it->getUnitCode() == unit_c){
			return it->getExplosive();
		}
	}
	return -1;
}

int infoUnits::getUnitToCreate(int unit_c){
	for (auto it = plantillas.begin(); it != plantillas.end(); ++it){
		if (it->getUnitCode() == unit_c){
			return it->getUnitToCreate();
		}
	}
	return -1;
}

int infoUnits::getFabTime(int unit_c){
	for (auto it = plantillas.begin(); it != plantillas.end(); ++it){
		if (it->getUnitCode() == unit_c){
			return it->getFabTime();
		}
	}
	return -1;
}

int infoUnits::getShootTime(int unit_c){
	for (auto it = plantillas.begin(); it != plantillas.end(); ++it){
		if (it->getUnitCode() == unit_c){
			return it->getShootTime();
		}
	}
	return -1;
}

int infoUnits::getTechLvl(int unit_c){
	for (auto it = plantillas.begin(); it != plantillas.end(); ++it){
		if (it->getUnitCode() == unit_c){
			return it->getTechLvl();
		}
	}
	return -1;
}

int infoUnits::getQuantToFab(int unit_c){
	for (auto it = plantillas.begin(); it != plantillas.end(); ++it){
		if (it->getUnitCode() == unit_c){
			return it->getQuantToFab();
		}
	}
	return -1;
}

void infoUnits::print(){
	for (auto it = plantillas.begin(); it != plantillas.end(); ++it){
		std::cout << "-------------------------" << std::endl;
		it->print();
	}
}