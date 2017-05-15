#include "unit.h"

unit::unit(int arma_code, int shoot_f, int range, double h, 
int f_time, int t_lvl): arma(armament(arma_code)), shoot_freq(shoot_f), 
range(range), health(h), fab_time(f_time), min_tech_lvl(t_lvl) {};

//necesito un tiempo para calcular el daño
double unit::getDamage(int time){
	return (this->arma.getBaseDamage() * time) / this->shoot_freq;
}

int unit::receiveDamage(double dam){
	if (health - dam < 0) return UNIT_DEAD;
	else health -= dam;
	return DAMAGE_TAKEN;
}