#ifndef INFOUNITS_H
#define INFOUNITS_H


#include <vector>
#include <map>
#include "unit.h"

class unitPlantilla {
private:
int unit_c;
int class_c;
int height;
int width;
int health;
int blocking; 
int speed;
int range_u;
int damage;
bool explosive;
int unit_to_create;
int fab_time;
int	shoot_time;
int tech_lvl;
int quant_fab;

public:
    unitPlantilla(int,int,int,int,int,int,int,int,int,bool,int,int,int,int,int);
	void print();
	int getUnitCode();
	int getClassCode();
	int getHeight();
	int getWidth();
	int getHealth();
	int getBlocking();
	int getSpeed();
	int getRange();
	int getDamage();
	bool getExplosive();
	int getUnitToCreate();
	int getFabTime();
	int getShootTime();
	int getTechLvl();
	int getQuantToFab();

};

class infoUnits {
private:
	std::vector<unitPlantilla> plantillas;
public:
    infoUnits(std::string &file_path);
	void print();
	void addInfo(unitPlantilla &up);
	int getClassCode(int unit_c);
	int getHeight(int unit_c);
	int getWidth(int unit_c);
	int getHealth(int unit_c);
	int getBlocking(int unit_c);
	int getSpeed(int unit_c);
	int getRange(int unit_c);
	int getDamage(int unit_c);
	bool getExplosive(int unit_c);
	int getUnitToCreate(int unit_c);
	int getFabTime(int unit_c);
	int getShootTime(int unit_c);
	int getTechLvl(int unit_c);
	int getQuantToFab(int unit_c);
};

#endif