#include "unit.h"
/*
unit::unit(int arma_code, int shoot_f, int range, double h, 
int f_time, int t_lvl): arma(armament(arma_code)), shoot_freq(shoot_f), 
range(range), health(h), fab_time(f_time), min_tech_lvl(t_lvl) {};

//necesito un tiempo para calcular el daño
double unit::getDamage(double time){
	return (this->arma.getBaseDamage() * time) / this->shoot_freq;
}

int unit::receiveDamage(double dam){
	if (health - dam < 0) return UNIT_DEAD;
	else health -= dam;
	return DAMAGE_TAKEN;
}
*/
void unit::setDestiny(int d_x, int d_y){
	dest_x = d_x;
	dest_y = d_y;
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