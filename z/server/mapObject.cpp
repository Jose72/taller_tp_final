#include "mapObject.h"

mapObject::mapObject(double h): health(h) {}

int mapObject::receiveDamage(double dam){
	if (health - dam < 0) return OBJECT_DESTROYED;
	else health -= dam;
	return DAMAGE_TAKEN;
}