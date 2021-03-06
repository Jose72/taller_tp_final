#ifndef CONSTANTS_H
#define CONSTANTS_H

/*
int getClassCodeFromUnit(int unit_c);
int getSpeedFromUnit(int unit_c);
int getHealthFromUnit(int unit_c);
int getFabTimeFromUnit(int unit_c);
int getTechLvlFromUnit(int unit_c);
*/
enum class_units {ROBOT = 20, VEHICLE = 21, BUILDING = 22, FLAG_C = 23, BULLET = 24, BRIDGE_C = 25, BLOCK = 26};

enum units {
	GRUNT = 0, PSYCHO = 1, TOUGHT = 2, PYRO = 3, SNIPER = 4, LAZER = 5, 
	JEEP = 6, MEDIUM_TANK = 7, LIGHT_TANK = 8, HEAVY_TANK = 9, MML = 10, 
	FORT = 11, ROBOT_FACTORY = 12, VEHICLE_FACTORY = 13, 
	FLAG = 14, 
	LLAMAS = 15, HCP = 16, LASER = 17, MISIL = 18, BALAS = 19, 
	BRIDGE_V = 20, BRIDGE_H = 21,  //puente horiz y vert
	ROCK = 22, ICE_B = 23, 
	BRIDGE_V_WOOD = 24, BRIDGE_H_WOOD = 25};

enum unit_speed { //veocidad (por seg ?)
		ROBOT_SPEED = 4, JEEP_SPEED = 8, MEDIUM_TANK_SPEED = 5, 
		LIGHT_TANK_SPEED = 6, HEAVY_TANK_SPEED = 5, MML_SPEED = 5,  
		BULLET_SPEED = 14, INSTA_BULLET_SPEED = 5000};

enum base_health {GRUNT_HEALTH = 60, PSYCHO_HEALTH = 80, TOUGHT_HEALTH = 300, 
PYRO_HEALTH = 100, SNIPER_HEALTH = 80, LAZER_HEALTH = 100, JEEP_HEALTH = 60, 
MEDIUM_TANK_HEALTH = 120, LIGHT_TANK_HEALTH = 80, HEAVY_TANK_HEALTH = 180, 
MML_HEALTH = 200, BUILDING_HEALTH = 1000 };

enum weapon_damage {BALAS_D = 2, LANZALLAMAS_D = 10, PROYECTILES_D = 20, 
LASER_D = 10, MISILES_D = 25 };

enum fabrication_time { GRUNT_F_TIME = 575, PSYCHO_F_TIME = 600, 
TOUGHT_F_TIME = 742, PYRO_F_TIME = 840, SNIPER_F_TIME = 575, LAZER_F_TIME = 900,
JEEP_F_TIME = 660, MEDIUM_TANK_F_TIME = 1080, LIGHT_TANK_F_TIME = 840, 
HEAVY_TANK_F_TIME = 1200, MML_F_TIME = 1320 };

enum unit_tech_level { GRUNT_TL = 1, PSYCHO_TL = 2,
TOUGHT_TL = 2, PYRO_TL = 4, SNIPER_TL = 3, LAZER_TL = 5,
JEEP_TL = 1, MEDIUM_TANK_TL = 3, LIGHT_TANK_TL = 2, 
HEAVY_TANK_TL = 4, MML_TL = 5 };

//miliseconds
#define GRUNT_SF 500 //(2*seg)
#define PSYCHO_SF 100
#define TOUGHT_SF 500
#define PYRO_SF 250
#define SNIPER_SF 250
#define LAZER_SF 250
#define JEEP_SF 166
#define MEDIUM_TANK_SF 2000
#define LIGHT_TANK_SF 2000
#define HEAVY_TANK_SF 2000
#define MML_SF 500

#define FLAG_CAPTURE_TIME 30000 //30 segs


//pixeles (tendria que ser otra cosa, es muy corto)
enum range {GRUNT_RANGE = 7, PSYCHO_RANGE = 7, TOUGHT_RANGE = 5, 
PYRO_RANGE = 6, SNIPER_RANGE = 10, LAZER_RANGE = 7, JEEP_RANGE = 6, 
MEDIUM_TANK_RANGE = 7, LIGHT_TANK_RANGE = 6, HEAVY_TANK_RANGE = 8, 
MML_RANGE = 8, FLAG_RANGE = 8, BULLET_RANGE = 3};

//enumerados
//no hace anda, bloquea y deja pasar
enum block_cod {B_NOTHING, B_BLOCK, B_LET_PASS};

#endif

