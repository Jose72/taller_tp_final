#ifndef UNIT_H
#define UNIT_H

#include "armament.h"

#define DAMAGE_TAKEN 0
#define UNIT_DEAD 1

enum class_units {ROBOT, VEHICLE, OT_OBJECT};

enum units {GRUNT, PSYCHO, TOUGHT , PYRO, SNIPER, LASER, 
JEEP, MEDIUM_TANK, LIGHT_TANK, HEAVY_TANK, MML};

enum unit_speed { //veocidad (por seg ?)
		ROBOT_SPEED = 4, JEEP_SPEED = 8, MEDIUM_TANK_SPEED = 5, 
		LIGHT_TANK_SPEED = 6, HEAVY_TANK_SPEED = 5, MML_SPEED = 5
	};

enum base_health {GRUNT_HEALTH = 60, PSYCHO_HEALTH = 80, TOUGHT_HEALTH = 300, 
PYRO_HEALTH = 100, SNIPER_HEALTH = 80, LASER_HEALTH = 100, JEEP_HEALTH = 60, 
MEDIUM_TANK_HEALTH = 120, LIGHT_TANK_HEALTH = 80, HEAVY_TANK_HEALTH = 180, 
MML_HEALTH = 200};

class unit {
	protected:
		int class_id;
		int unit_id;
		int x;
		int y;
		int dest_x;
		int dest_y;
		int b_health;
		int health;
		int speed;
		int dps;
		/*
		armament arma;
		int shoot_freq; //en segundos
		int range;
		int fab_time; //en segundos
		int min_tech_lvl;
		*/
	public:
		unit(int class_id, int unit_id, int x, int y, int health, int speed);
		void setPos(int p_x, int p_y);
		bool isMoving();
		int getUnitId();
		int getClassId();
		int getX();
		int getY();
		int getDestX();
		int getDestY();
		void printPos();
		int getSpeed();
		double getRelativeDamage();
		void move(int d_x, int d_y);
		int getDps();
		//double getDamage(double time); 
		//int receiveDamage(double dam);
};

#endif
