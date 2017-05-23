#include "unit.h"
#include <iostream>
#include "math.h"
/*
unit::unit(int arma_code, int shoot_f, int range, double h, 
int f_time, int t_lvl): arma(armament(arma_code)), shoot_freq(shoot_f), 
range(range), health(h), fab_time(f_time), min_tech_lvl(t_lvl) {};

//necesito un tiempo para calcular el daño
double unit::getDamage(double time){
	return (this->arma.getBaseDamage() * time) / this->shoot_freq;
}


*/
unit::unit(int class_id, int unit_id, int x, int y, int health, int speed): class_id(class_id), 
unit_id(unit_id), x(x), y(y), dest_x(x), dest_y(y), b_health(health), health(health), 
speed(speed), arma(armament(unit_id)) {};

unit::unit(int class_id, int unit_id, int x, int y, int health, int speed, 
double shoot_f, int rang, double fab_time, int min_t): 
class_id(class_id), unit_id(unit_id), x(x), y(y), dest_x(x), dest_y(y), 
b_health(health), health(health), speed(speed), arma(armament(unit_id)), shoot_freq(shoot_f), 
range_u(rang), fab_time(fab_time), min_tech_lvl(min_t) {};
	
	


void unit::setPos(int p_x, int p_y){
	x = p_x;
	y = p_y;
}


bool unit::isMoving(){
	if (x != dest_x || y != dest_y) return true;
	return false;
};

int unit::getUnitId(){
	return unit_id;
}

int unit::getClassId(){
	return class_id;
}

int unit::getX(){
	return x;
}

int unit::getY(){
	return y;
}

int unit::getDestX(){
	return dest_x;
}

int unit::getDestY(){
	return dest_y;
}

void unit::printPos(){
	std::cout << "unit--------" << std::endl;
	//std::cout << "class_id: " << class_id << std::endl;
	//std::cout << "unit_id: " << unit_id << std::endl;
	std::cout << "x_pos: " << x << std::endl;
	std::cout << "y_pos: " << y << std::endl;
	std::cout << "health: " << health << std::endl;
}

int unit::getSpeed(){
	return speed;
}

double unit::getRelativeDamage(){
	return ((b_health - health) / (double) b_health);
}

void unit::move(int d_x, int d_y){
	dest_x = d_x;
	dest_y = d_y;
}

void unit::stop(){
	dest_x = x;
	dest_y = y;
}

bool unit::isInRange(unit &u, int range){
	if (sqrt(pow((this->x - u.x),2) + pow((this->y - u.y),2)) <= range) {
		return true;
	}
	return false;
}

int unit::takeDamage(int dam){
	if (health - dam < 0) return UNIT_DEAD;
	else health = health - dam;
	return DAMAGE_TAKEN;
}

void unit::setAttack(unit *u){
	attacking = u;
}


/*
unitMovable::unitMovable(int class_id, int unit_id, int x, int y): unit(class_id, unit_id, 
x, y), dest_x(x), dest_y(y), attacking(nullptr), arma(armament(unit_id)){
	switch (unit_id) {
		case GRUNT:
			shoot_freq = 2;
			range = 7;
		case PSYCHO:
			shoot_freq = 10;
			range = 7;
		case TOUGHT: 
			shoot_freq = 2;
			range = 5;
		case PYRO:
			shoot_freq = 10;
			range = 7;
		case SNIPER: 
			shoot_freq = 4;
			range = 10;
		case LAZER: 
			shoot_freq = 4;
			range = 7;
		case JEEP:
			shoot_freq = 6;
			range = 6;
		case MML: 
			shoot_freq = 2;
			range = 8;
		case MEDIUM_TANK:
			shoot_freq = 0.5;
			range = 7;
		case LIGHT_TANK:
			shoot_freq = 0.5;
			range = 6;
		case HEAVY_TANK:
			shoot_freq = 0.5;
			range = 6;
		default:
			shoot_freq = 0;
			range = 0;
	}
}
*/