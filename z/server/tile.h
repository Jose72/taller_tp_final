#ifndef TILE_H
#define TILE_H

#include "terrain.h"
//#include "Map.h"

#define TILE_LENGHT 10//medida lado de la casilla, valor a definir


class tile{
	private:
		//cada casilla guarda su punto central
		int x_cord;
		int y_cord;
		terrain terr;
		//terrain terrain; // deberia ser puntero, para hacer polimorfismo con los tipos de terrenos
		bool blocked; //solo para testeos!!
		//Unit *unit; puntero a unidad, si alguna unidad esta en la casilla, si no hay entonces null.
		
		//en vez de reserva memoria por cada casilla, se podria tener un vector de terrenos y unidades
		//cada vec tiene las unidades/terrenos posibles y pasa el puntero correspondiente
		//o sea, hay una entrada en el vector por cada unidad/terreno desde el principio
		//no se agrega si se saca nada mas
		//si hay threads puede haber problemas, pero se podria controlar accesos con un mutex (poco eficiente??)
		
		//para el a*
		tile *parent;
		double h;
		double g;
		
		
	public:
		tile(int x, int y, int terrain_id);
		int getX();
		int getY();
		tile* getParent();
		void setParent(tile *p);
		double fValue(tile &dest);
		double gValue();                   //hacer gValue, hValue por fuera de tiles !!!!!!!
		double hValue(tile &dest);
		void setG(double g);
		void setH(double h);
		double getG();
		double getH();
		void setH(tile &dest);
		bool operator<(tile &t);
		bool isPassable(int unit_code); //chequea si el terreno es pasable y si no hay unidades/edificios en la casilla
		bool isEqual(tile &t); //comparacion para el a*
		bool isOcupied();//si hay alguna unidad/edificio sobre la casilla
		double dist(tile &t); //distancia entre casillas
		void printTile();
		bool isDiagonal(tile &t);

};


#endif
