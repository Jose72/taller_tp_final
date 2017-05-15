#ifndef MAPOBJECT_H
#define MAPOBJECT_H


#define DAMAGE_TAKEN 0
#define OBJECT_DESTROYED 1

class mapObject {
	protected:
		double health;
	public:
		mapObject(double h);
		int receiveDamage(double dam);
};

#endif