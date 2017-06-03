#include "unit.h"
#include <iostream>
#include "math.h"

unit::unit(int owner, int unit_id, int x, int y): owner(owner), unit_id(unit_id), x(x), y(y), 
dest_x(x), dest_y(y), target(nullptr) {
	class_id = getClassCodeFromUnit(unit_id);
	speed = getSpeedFromUnit(unit_id);
	b_health = getHealthFromUnit(unit_id);
	health = b_health;

	
};

unit::unit(int owner, int class_id, int unit_id, 
int x, int y, int health, int state, int speed, int a_range, int base_damage, int base_time, 
int unit_to_c, int tech_level): owner(owner), class_id(class_id), unit_id(unit_id), x(x), y(y), 
b_health(health), health(health), state(state), dest_x(x), dest_y(y) ,speed(speed), 
target(nullptr), attack_range(a_range), base_damage(base_damage), base_time(base_time), 
countdown(base_time), unit_code_to_create(unit_to_c), tech_level(tech_level) {};



/*
unit::unit(int class_id, int unit_id, int x, int y, int health, int speed): 
class_id(class_id), unit_id(unit_id), x(x), y(y), dest_x(x), dest_y(y), 
b_health(health), health(health), speed(speed), attacking(nullptr) {
	attack_b = new attackBehaviour(unit_id);
	create_b = new createBehaviour(unit_id);
};	
*/


void unit::setPos(int p_x, int p_y){
	x = p_x;
	y = p_y;
}



//preguntar a los beaviours ???
bool unit::isMoving(){
	//pendiente: crear un moveBehaviour y chequear eso en vez del id de clase
	if ((x != dest_x || y != dest_y)) return true;
	return false;
};

bool unit::isAttacking(){
	//si tiene objetivo y ataq behaviour
	if (target && this->isEnemy(*target)) return true;
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
	state = MOVING;
}

void unit::attack(unit *u){
	if (u) {
		target = u;
		u->setFollower(this);
		if (this->isInTargetRange()){
			this->changeState(ATTACKING);
		} else {
			this->move(u->getX(), u->getY());
		}
	} 
}

void unit::stop(){
	dest_x = x;
	dest_y = y;
}

bool unit::isInRange(unit &u){
	if (sqrt(pow((this->x - u.x),2) + pow((this->y - u.y),2)) <= this->attack_range) {
		return true;
	}
	return false;
}

int unit::takeDamage(int dam){
	if (health - dam < 0) {
		health = 0;
		state = DEAD;
	}
	else health = health - dam;
	return DAMAGE_TAKEN;
}

void unit::setAttack(unit *u){
	if (u->owner != this->owner){
		target = u;
	}
	
}

int unit::attackRange(){
	return attack_range;
}

double unit::getDamage(){
	return base_damage;
}

unit* unit::getTarget(){
	return target;
}

void unit::printPosDest(){
	std::cout << "x: " << x << " d_x: " << dest_x << std::endl;
	std::cout << "y: " << y << " d_y: " << dest_y << std::endl;
}

bool unit::isEnemy(unit &u){
	//pendiente: chequear si el owner es mageMap 
	//(en el caso de que la unidad sea una piedra u otro objeto destruible)
	
	if (this->owner != u.owner) {
		for (auto it = allies.begin(); it != allies.end(); ++it){
			if ((*it) == u.owner) return false;
		}
		//if (0 == u.owner) return true; //es un objeto del mapa
		return true;
	}
	return false;
}


int unit::getOwner(){
	return owner;
}

bool unit::isAlive(){
	if (health > 0 && state != DEAD) return true;
	return false;
}


//countdown me dice cuando puedo atacar (cuando esta en 0)
//hay "espera" por la frecuencia de disparo
//
bool unit::canAttack(){
	return (countdown == 0);
}

//resto el tiempo del time slice al countdown
//el tiempo en milisegundos
void unit::actualizeTimer(int time){
	if (countdown - time < 0) {
		countdown = 0;
		return;
	}
	countdown = countdown - time;
}

//reseteo el countdown si acabo de disparar
void unit::resetTimer(){
	countdown = base_time;
}

int unit::unitToCreate(){
	return unit_code_to_create;
}

void unit::changeState(int s){
	state = s;
}

bool unit::isInTargetRange(){
	if (target) {
		if (sqrt(pow((x - target->x),2) + pow((y - target->y),2)) <= this->attack_range) {
		return true;
		}
	}
	return false;
}

void unit::moveToTarget(){
	if (target){
		this->move(target->getX(), target->getY());
		state = MOVING;
	}
}

bool unit::targetIsEnemy(){
	if (this->isEnemy(*target)) return true;
	return false;
}

int unit::getState(){
	return state;
}

void unit::setAllie(int a){
	allies.push_back(a);
}

//seteo a los que me estan siguiendo
//para cuando muera les aviso
void unit::setFollower(unit *u){
	followers.push_back(u);
}


//si estaba targeteando a la unidad, no lo hago mas
void unit::removeTarget(unit *u){
	if (target == u){
		target = nullptr;
	}
}

bool unit::isDead(){
	if (state == DEAD) return true;
	return false;
}