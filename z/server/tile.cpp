
#include "tile.h"
#include <stdlib.h>
#include <vector>
#include <map>
#include <math.h>  
#include <iostream>
#include <algorithm>

tile::tile(int x, int y, int terrain_id): x_cord(x), y_cord(y), terr(terrain(terrain_id)) {
	parent = nullptr;
	unit_over = false;
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
	if ((t.x_cord == this->x_cord) && (t.y_cord == this->y_cord)) return true;
	return false;
}

//chequea si se puede pasar por la casilla
//true si el terreno es pasable y si no hay unidades/edificios en la casilla
bool tile::isPassable(int unit_code){
	if (unit_over){
		return passable;
	} 
	return (terr.isPassable(unit_code));
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

double tile::getF(){
	return g + h;
}

void tile::printTile(){
	std::cout << "x: " << x_cord << std::endl;
	std::cout << "y: " << y_cord << std::endl;
	std::cout << terr.getTerrainFactor() << std::endl;
	std::cout << "g: " << g << std::endl;
	std::cout << "h: " << h << std::endl;
	std::cout << std::endl;

}

double tile::getTerrainFactor(){
	return terr.getTerrainFactor();
}

int tile::getTerrainCode(){
	return terr.getTerrainCode();
}

//si hay una undiad arriba
//seteo en bool el flg
//y pongo en pasable el bool indicado
void tile::putUnitOver(bool b){
	unit_over = true;
	passable = b;
}

void tile::releaseUnitOver(){
	unit_over = false;
}

void tile::setTerrain(int t_code){
	terr = terrain(t_code);
}