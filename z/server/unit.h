#ifndef UNIT_H
#define UNIT_H

#include <vector>
#include "../common/constants.h"
#define DAMAGE_TAKEN 0
#define UNIT_DEAD 1

enum states {NO_STATE, MOVING, ATTACKING, CREATING, DRIVING, DEAD, STANDING, CAPTURED, CHECKING_CAPTURE, DEFEATED, DESTROYED, ERASED, READY_TO_DIE};

class unit {
	protected:
		int unit_id;
		int class_id;
		int height;
		int width;
		int owner; //team number
		double x;
		double y;
		int b_health;
		int health;
		
		//estado
		int state;
		
		int blocking;
		
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
		bool explosive_damage;
		bool auto_attack;
		
		//creacion/ataque
		int base_time;
		double countdown;
		int unit_code_to_create;
		int quant_to_create;
		int tech_level;
		
		
	public:
		unit(int unit_id, int class_id, int height, int width, int owner, int x, int y, 
	int health, int state, int blocking, int speed, int a_range, int base_damage, bool explosive, 
	int base_time, int unit_to_c, int tech_level);
		void setPos(double p_x, double p_y);
		bool isMoving();
		int getUnitId();
		int getClassId();
		int getX();
		double getX_D();
		int getY();
		double getY_D();
		
		int getWidth();
		int getHeight();
		int getCenterX();
		int getCenterY();
		double getCenterX_D();
		double getCenterY_D();
		double getRadius();
		
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
		bool isExplosiveDamage();
		int getBlockingType();
		unit* getDriver();
		int getTimeToCompletion();
		
		//seters
		void changeState(int state);
		void changeOwnerForTargetOwner();
		void setTechLvl(int tl);
		void changeOwner(int o);
		void setDestiny(int x, int y);
		
		//events
		void move(int d_x, int d_y);
		void moveToTarget();
		void attack(unit *u);
		void stop();
		void drive(unit *vehicle);
		void driveTarget();
		void create(int u_id, int time);
		
		void instantDrive(unit *u);
		
		//checks
		bool isInRange(unit &u);
		bool isAlive();
		bool canAttack();
		bool isEnemy(unit *u);
		bool canCreate();
		bool autoAttackEnabled();
		bool targetIsInRange();
		bool canDriveTarget();
		bool isAttackable(unit *u);
		bool hasOnTop(unit *u);
		
		//double getDamage(double time); 
		int takeDamage(int dam, bool explosive);
		
		double getDamage();
		int attackRange();
		unit* getTarget();
		void printPosDest();
		bool targetIsEnemy();
		bool targetIsAttackable();
		bool sameOwnerAsTarget();
		
		//creacion-captura
		void actualizeTimer(int time); // para ataque
		void actualizeCaptureTimer(int time); // para ataque
		void updateCreationTimer(int time, int t_count); //para crear unidad
		void resetTimer();
		void resetAttackTimer();
		int unitToCreate();
		bool timerComplete();

		
		//targeting
		void setTarget(unit *u);
		void setAutoAttack(unit *u);
		void setFollower(unit *u);
		void removeFollower(unit* u);
		void removeTarget(unit *u);
		bool isFollowedBy(unit *u);
		void stopFollowers();
		void setFlagTarget(unit *);
	
};

#endif
