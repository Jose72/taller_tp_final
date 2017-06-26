#ifndef TILE_H
#define TILE_H

#include "terrain.h"

#define TILE_LENGHT 32//medida lado de la casilla, valor a definir


class tile{
	private:
		int x_cord;
		int y_cord;
		terrain terr;
		bool unit_over; //si hay unidad que afecta al terreno (puente, edificio, roca)
		bool passable; //si hay unidad arriba, me fijo aca si es pasable, en vez de ver el terreno
		
		
		//para el a*
		tile *parent;
		double h; //euristica
		double g;
		
		
	public:
		tile(int x, int y, int terrain_id);
		int getX();
		int getY();
		int getTerrainCode();
		void setTerrain(int t_code);
		tile* getParent();
		void setParent(tile *p);
		double gValue();           
		double hValue(tile &dest);
		void setG(double g);
		void setH(double h);
		double getG();
		double getH();
		double getF();
		void setH(tile &dest);
		bool operator<(tile &t);
		bool isPassable(int unit_code); 
		bool isDiagonal(tile &t);
		bool isEqual(tile &t); //comparacion para el a*
		double dist(tile &t); //distancia entre casillas
		void printTile();
		double getTerrainFactor();
		void putUnitOver(bool b);
		void releaseUnitOver();
		double euclideanDist(tile*);

};


#endif
