#ifndef TILE_H
#define TILE_H

#include "Terrain.h"

#define TILE_LENGHT 10//medida lado de la casilla

class Tile{
	private:
		//cada casilla guarda su punto central
		int x_cord;
		int y_cord;
		//Terrain terrain; // deberia ser puntero, para hacer polimorfismo con los tipos de terrenos
		bool blocked; //solo para testeos!!
		//Unit *unit; puntero a unidad, si alguna unidad esta en la casilla, si no hay entonces null.
		
		//en vez de reserva memoria por cada casilla, se podria tener un vector de terrenos y unidades
		//cada vec tiene las unidades/terrenos posibles y pasa el puntero correspondiente
		//o sea, hay una entrada en el vector por cada unidad/terreno desde el principio
		//no se agrega si se saca nada mas
		//si hay threads puede haber problemas, pero se podria controlar accesos con un mutex (poco eficiente??)
		
		//para el a*
		Tile *parent;
		int fValue(Tile &dest);
		int gValue();
		int hValue(Tile &dest);
		
	public:
		Tile(int x, int y);
		int getX();
		int getY();
		bool isPassable(); //chequea si el terreno es pasable y si no hay unidades/edificios en la casilla
		bool isEqual(Tile &t); //comparacion para el a*
		bool isOcupied();//si hay alguna unidad/edificio sobre la casilla
		int dist(Tile &t); //distancia entre casillas
		int moveTo(Tile &t); //a*
	
};


#endif