
#include "tile.h"
#include <stdlib.h>
#include <vector>
#include <map>
#include <math.h>  
#include <iostream>

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
	/*
	(terrain.isPassable && this->isOcupied) return true;
	return false
	*/
	return true;
}

int tile::dist(tile &t){
	//distancia manhattan (si no se puede mover en diagonal)
	return sqrt(pow((this->x_cord - t.x_cord),2)) + sqrt(pow((this->y_cord - t.y_cord),2));
}

int tile::gValue(){
	//costo siguiendo el camino generado
	tile *aux = this;
	int movs = -1;
	//voy hacia  atras con parent, y veo cant de movimientos
	while (aux != nullptr){
		aux = aux->parent;
		movs++;
	}
	return movs;
}

int tile::hValue(tile &dest){
	//distancia manhattan como aprox
	//distancia / largo casilla = movs
	//std::cout << "dx " << this->x_cord - dest.x_cord << " dy "<< this->y_cord - dest.y_cord << std::endl;
	return sqrt(pow((this->x_cord - dest.x_cord),2)) +sqrt(pow((this->y_cord - dest.y_cord), 2)) ;
}

int tile::fValue(tile &dest){
	//f = g + h
	return gValue()+hValue(dest);
}

bool tile::operator<(tile &t){
	return (this->g + this->h) < (t.g + t.h);
}

void tile::setG(int g){
	this->g = g;
}

void tile::setH(int h){
	this->h = h;
}

void tile::setH(tile &dest){
	this->h = this->hValue(dest);
}

int tile::getG(){
	return g;
}

int tile::getH(){
	return h;
}

void tile::printTile(){
	std::cout << "x: " << x_cord << std::endl;
	std::cout << "y: " << y_cord << std::endl;
	std::cout << std::endl;
}