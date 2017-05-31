#ifndef UNIT_H
#define UNIT_H

#include "constants.h"
#include "armament.h"
#include "behaviour.h"
#include "attackBehaviour.h"
#include "createBehaviour.h"

#define DAMAGE_TAKEN 0
#define UNIT_DEAD 1



class unit {
	protected:
		int owner;
		std::vector<int> allies;
		int class_id;
		int unit_id;
		int x;
		int y;
		int b_health;
		int health;
		
		//movimiento
		int dest_x;
		int dest_y;
		int speed;
		
		//ataque
		unit *attacking;
		int attack_range;
		int base_damage;
		
		//creacion o ataque
		int base_time;
		int countdown;
		int tech_level;
		
		//bandera
		
		
		
		/*
		armament arma;
		int shoot_freq; //en segundos
		int range;
		int fab_time; //en segundos
		int min_tech_lvl;
		*/
	public:
		unit(int owner, int unit_id, int x, int y);
		unit(int owner, int class_id, int unit_id, std::vector<int> &allies, 
int x, int y, int health, int speed, int a_range, int base_damage, int base_time, int tech_level);
		void setPos(int p_x, int p_y);
		bool isMoving();
		bool isAttacking();
		bool isCreating();
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
		void stop();
		bool isInRange(unit &u, int range);
		//double getDamage(double time); 
		int takeDamage(int dam);
		void setAttack(unit *u);
		double getDamage();
		int attackRange();
		unit* getTarget();
		void printPosDest();
		bool isEnemy(unit &u);
		int checkCreating(double time);
		void destroy();
		int getOwner();
		bool isAlive();
};

#endif
