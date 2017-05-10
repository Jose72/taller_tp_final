#include "tilesListCost.h"
#include <algorithm>

void tilesListCost::insert(tile &t){
	casillas.push_back(t);
	sort(casillas.begin(), casillas.end());
}

void tilesListCost::eraseIfFound(tile &t){
	for (auto it = casillas.begin(); it != casillas.end(); ++it){
		if (it->isEqual(t)){
			it = casillas.erase(it);
		}
	}
}

bool tilesListCost::found(tile &t){
	for (auto it = casillas.begin(); it != casillas.end(); ++it){
		if (it->isEqual(t)){
			return true;
		}
	}
	return false;
}

bool tilesListCost::empty(){
	return casillas.empty();
}

tile tilesListCost::begin() {
	return *casillas.begin();
}

int tilesListCost::foundReplaceOrInsert(tile &t){
	for (auto it = casillas.begin(); it != casillas.end(); ++it){
		if (it->isEqual(t)){
			if (it->getG() < t.getG()){
				return FOUND_BETTER_G;
			} else {
				//si el que esta tiene mayor g
				//reemplazo g y parent;
				it->setG(t.getG());
				it->setParent(t.getParent());
				return FOUND_WORST_G;
			}
		}
	}
	//si no lo encontre inserto;
	this->insert(t);
	return NOT_FOUND;
}