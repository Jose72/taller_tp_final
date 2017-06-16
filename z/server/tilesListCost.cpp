#include "tilesListCost.h"
#include <algorithm>
#include <iostream>

void tilesListCost::insert(tile *t){
	casillas.push_back(t);
	//sort(casillas.begin(), casillas.end());
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

int tilesListCost::foundReplaceOrInsert(tile *t){
	for (auto it = casillas.begin(); it != casillas.end(); ++it){
		if ((*it)->isEqual(*t)){
			if ((*it)->getG() < t->getG()){
				return FOUND_BETTER_G;
			} else {
				//si el que esta tiene mayor g
				//reemplazo g y parent;
				if (t->getX() == 8 && t->getY() == 6){
					std::cout << "BADDDDDDDDDDDDDDD" << std::endl;
					(*it)->printTile();
					t->printTile();
					std::cout << "BADDDDDD" << std::endl;
				}
				(*it)->setG(t->getG());
				(*it)->setParent(t->getParent());
				return FOUND_WORST_G;
			}
		}
	}
	//si no lo encontre inserto;
	this->insert(t);
	//sort(casillas.begin(), casillas.end());
	return NOT_FOUND;
}

int tilesListCost::size(){
	return casillas.size();
}

void tilesListCost::print(){
	for (auto it = casillas.begin(); it != casillas.end(); ++it){
			(*it)->printTile();
		}
	}
