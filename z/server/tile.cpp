
#include "tile.h"
#include <stdlib.h>
#include <vector>
#include <map>
#include <math.h>  
#include <iostream>
#include <algorithm>

tile::tile(int x, int y, int terrain_id): x_cord(x), y_cord(y), terr(terrain(terrain_id)) {
	parent = nullptr;
}

//retorna coordenada x de la casilla
int tile::getX(){
	return x_cord;
}

//retorna coordenada y de la casilla
int tile::getY(){
	return y_cord;
}

tile* tile::getParent(){
	return parent;
}

void tile::setParent(tile *p){
	parent = p;
}

//chequea si las casillas sin iguales en el mapa
//solo cuequea coordenadas
bool tile::isEqual(tile &t){
	if (t.x_cord == this->x_cord && t.y_cord == this->y_cord) return true;
	return false;
}

//chequea si se puede pasar por la casilla
//true si el terreno es pasable y si no hay unidades/edificios en la casilla
bool tile::isPassable(int unit_code){
	if (terr.isPassable(unit_code)) return true;
	return false;

}


//solo para casillas adyacentes
double tile::dist(tile &t){
	/*
	//si es diagonal costo es +0.4
	if (this->isDiagonal(t)) {
		return 0.4 + t.gValue();
	}
	*/
	return t.gValue();
	
}


//costo de moverse a esta casilla desde una vecina no diagonal
double tile::gValue(){
	return (2 - terr.getTerrainFactor());
}

double tile::hValue(tile &dest){
	//distancia euclideana
	return sqrt(pow((this->x_cord - dest.x_cord),2) + pow((this->y_cord - dest.y_cord),2)) ;
	//distancia diagonal
	//return std::max((abs(this->x_cord - dest.x_cord)), (abs(this->y_cord - dest.y_cord)));
	//distancia manhattan
	//return sqrt(pow((this->x_cord - dest.x_cord),2)) +sqrt(pow((this->y_cord - dest.y_cord), 2)) ;
}


bool tile::operator<(tile &t){
	return (this->g + this->h) < (t.g + t.h);
}

void tile::setG(double g){
	this->g = g;
}

void tile::setH(double h){
	this->h = h;
}

void tile::setH(tile &dest){
	this->h = this->hValue(dest);
}

double tile::getG(){
	return g;
}

double tile::getH(){
	return h;
}

void tile::printTile(){
	std::cout << "x: " << x_cord << std::endl;
	std::cout << "y: " << y_cord << std::endl;
	std::cout << std::endl;
}

bool tile::isDiagonal(tile &t){
	if (x_cord == 1 + t.x_cord && y_cord == 1 + t.y_cord) return true;
	if (x_cord == 1 + t.x_cord && y_cord == -1 + t.y_cord) return true;
	if (x_cord == -1 + t.x_cord && y_cord == 1 + t.y_cord) return true;
	if (x_cord == -1 + t.x_cord && y_cord == -1 + t.y_cord) return true;
	return false;
}

double tile::getTerrainFactor(){
	return terr.getTerrainFactor();
}