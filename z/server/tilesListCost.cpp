#include "tilesListCost.h"
#include <algorithm>
#include <iostream>

void tilesListCost::insert(tile *t){
	casillas.push_back(t);
}

void tilesListCost::eraseIfFound(tile *t){
	for (auto it = casillas.begin(); it != casillas.end(); ++it){
		if ((*it)->isEqual(*t)){
			it = casillas.erase(it);
			return;
		}
	}
}

bool tilesListCost::found(tile *t){
	for (auto it = casillas.begin(); it != casillas.end(); ++it){
		
		if ((*it)->isEqual(*t)){
			return true;
		}
	}
	return false;
}

bool tilesListCost::empty(){
	return casillas.empty();
}

tile* tilesListCost::begin() {
	if (casillas.empty()) return nullptr;
	tile *aux = *casillas.begin();
	for (auto it = casillas.begin(); it != casillas.end(); ++it){
		if ((*it)->getF() < aux->getF()){
			aux = *it;
		}
	}
	return aux;
}

int tilesListCost::size(){
	return casillas.size();
}

void tilesListCost::print(){
	for (auto it = casillas.begin(); it != casillas.end(); ++it){
			(*it)->printTile();
		}
	}

