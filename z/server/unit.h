#ifndef UNIT_H
#define UNIT_H

#include "armament.h"

#define DAMAGE_TAKEN 0
#define UNIT_DEAD 1

enum class_units {ROBOT, VEHICLE, OT_OBJECT};

enum units {GRUNT, PSYCHO, TOUGHT , PYRO, SNIPER, LASER, 
			JEEP, MEDIUM_TANK, LIGHT_TANK, HEAVY_TANK, MML
};

class unit {
	protected:
		int class_id;
		int unit_id;
		int x;
		int y;
		int dest_x;
		int dest_y;
		double health;
		/*
		armament arma;
		int shoot_freq; //en segundos
		int range;
		int fab_time; //en segundos
		int min_tech_lvl;
		*/
	public:
		unit(int class_id, int unit_id, int x, int y, double health);
		void setPos(int p_x, int p_y);
		void setDestiny(int d_x, int d_y);
		bool isMoving();
		int getUnitId();
		int getClassId();
		int getX();
		int getY();
		int getDestX();
		int getDestY();
		void printPos();
		//double getDamage(double time); //necesito un tiempo para calcular el daño
		//int receiveDamage(double dam);
};

#endif
