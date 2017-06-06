#ifndef UNIT_H
#define UNIT_H

#include "constants.h"
#include "armament.h"
#include <vector>
#define DAMAGE_TAKEN 0
#define UNIT_DEAD 1

enum states {NO_STATE, MOVING, ATTACKING, CREATING, DRIVING, DEAD, STANDING, CAPTURED, CHECKING_CAPTURE};

class unit {
	protected:
		int unit_id;
		int class_id;
		int owner;
		std::vector<int> allies;
		int x;
		int y;
		int b_health;
		int health;
		
		int state;
		
		//movimiento
		int dest_x;
		int dest_y;
		int speed;
		
		//conduccion
		unit *driver;
		
		//ataque
		std::vector<unit*> followers;
		unit *target;
		int attack_range;
		int base_damage;
		bool auto_attack;
		
		//creacion o ataque
		int base_time;
		int countdown;
		int unit_code_to_create;
		int tech_level;
		
		//bandera
		
		
	public:
		unit(int unit_id, int owner, int x, int y);
		unit(int unit_id, int class_id, int owner, int x, int y, 
	int health, int state, int speed, int a_range, int base_damage, 
	int base_time, int unit_to_c, int tech_level);
		void setPos(int p_x, int p_y);
		bool isMoving();
		int getUnitId();
		int getClassId();
		int getX();
		int getY();
		int getDestX();
		int getDestY();
		int getHealth();
		void printPos();
		int getSpeed();
		int getOwner();
		int getTechLvl();
		int getState();
		double getRelativeDamage();
		int getTargetOwner();
		
		//seters
		void changeState(int state);
		void changeOwnerForTargetOwner();
		void decreaseTechLvl();
		void increaseTechLvl();
		
		//events
		void move(int d_x, int d_y);
		void moveToTarget();
		void attack(unit *u);
		void stop();
		void drive(unit *vehicle);
		void driveTarget();
		
		//checks
		bool isInRange(unit &u);
		bool isAlive();
		bool isDead();
		bool canAttack();
		bool isEnemy(unit &u);
		bool canCreate();
		bool autoAttackEnabled();
		bool timerIsZero();
		bool targetIsInRange();
		bool canDriveTarget();
		bool isDriving();

		//double getDamage(double time); 
		int takeDamage(int dam);
		
		double getDamage();
		int attackRange();
		unit* getTarget();
		void printPosDest();
		bool targetIsEnemy();
		bool sameOwner(unit *u);
		bool sameOwnerAsTarget();
		
		int checkCreating(double time);
		void destroy();
		
		//creacion-captura
		void actualizeTimer(int time);
		void resetTimer();
		int unitToCreate();
		
		//targeting
		void setTarget(unit *u);
		void setAutoAttack(unit *u);
		void setAllie(int a);
		void setFollower(unit *u);
		void removeFollower(unit* u);
		void removeTarget(unit *u);
		void setAttack(unit *u);
		bool isFollowedBy(unit *u);
		void stopFollowers();
	
};

#endif
