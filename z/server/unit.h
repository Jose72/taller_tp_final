#ifndef UNIT_H
#define UNIT_H

#include "constants.h"
#include "armament.h"

#define DAMAGE_TAKEN 0
#define UNIT_DEAD 1



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
		//Attack attack_b;
		unit *attacking;
		armament arma;
		double shoot_freq; //en segundos
		int range_u;
		int fab_time; //en segundos
		int min_tech_lvl;
		/*
		armament arma;
		int shoot_freq; //en segundos
		int range;
		int fab_time; //en segundos
		int min_tech_lvl;
		*/
	public:
		unit(int class_id, int unit_id, int x, int y, int health, int speed);
		unit(int class_id, int unit_id, int x, int y, int health, int speed, 
		double shoot_f, int rang, double fab_time, int min_t);
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
		bool isInRange(unit &u, int range);
		//double getDamage(double time); 
		int takeDamage(int dam);
		void setAttack(unit *u);
};

#endif
