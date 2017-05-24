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
speed(speed), attacking(nullptr), attack_b(attackBehaviour(unit_id)) {};

	
	


void unit::setPos(int p_x, int p_y){
	x = p_x;
	y = p_y;
}



//preguntar a los beaviours ???
bool unit::isMoving(){
	if (x != dest_x || y != dest_y) return true;
	return false;
};

bool unit::isAttacking(){
	if (attacking) return true;
	return false;
}

bool unit::isCreating(){
	return false;
}
//////



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

int unit::attackRange(){
	return attack_b.getRange();
}

double unit::getDamage(double time){
	return attack_b.getDamage(time);
}

unit* unit::getTarget(){
	return attacking;
}

void unit::printPosDest(){
	std::cout << "x: " << x << " d_x: " << dest_x << std::endl;
	std::cout << "y: " << y << " d_y: " << dest_y << std::endl;
}