
#include "Tile.h"
#include <map>
#include <stdlib.h>
#include <vector>

Tile::Tile(int x, int y): x_cord(x), y_cord(y) {
	parent = nullptr;
}

//retorna coordenada x de la casilla
int Tile::getX(){
	return x_cord;
}

//retorna coordenada y de la casilla
int Tile::getY(){
	return y_cord;
}

//chequea si las casillas sin iguales en el mapa
//solo cuequea coordenadas
bool Tile::isEqual(Tile &t){
	if (t.x_cord == this->x_cord && t.y_cord == this->y_cord) return true;
	return false;
}

//chequea si se puede pasar por la casilla
//true si el terreno es pasable y si no hay unidades/edificios en la casilla
bool Tile::isPassable(){
	/*
	(terrain.isPassable && this->isOcupied) return true;
	return false
	*/
	return true;
}

int Tile::dist(Tile &t){
	//distancia manhattan (si no se puede mover en diagonal)
	return abs(this->x_cord - t.x_cord) + abs(this->y_cord - t.y_cord);
}

int Tile::gValue(){
	//costo siguiendo el camino generado
	Tile *aux = this->parent;
	int movs = 0;
	//voy hacia  atras con parent, y veo cant de movimientos
	while (aux->parent != nullptr){
		aux = parent;
		movs++;
	}
	return movs;
}

int Tile::hValue(Tile &dest){
	//distancia manhattan como aprox
	//distancia / largo casilla = movs
	return abs(this->x_cord - dest.x_cord) + abs(this->y_cord - dest.y_cord) / TILE_LENGHT;
}

int Tile::fValue(Tile &dest){
	//f = g + h
	return gValue()+hValue(dest);
}


//buscar el mejor camino a la casilla destino
int Tile::moveTo(Tile &dest){
//necesitaria referencia al mapa??


//se ordena con el f, seria una especie de costo por moverse
//cada casilla tiene uno, lo uso para buscar el camino hasta el destino
//f = g + h
//g = costo por moverme desde el origen hasta la casilla actual, por el camino elegido hasta el momento
//h = costo por moverme desde la casilla actual hasta el destino (se aproxima en gral)

//nodos visitados, pero no expandidos
std::map<int, Tile> open;
//nodos visitados, y expandidos
std::map<int, Tile> closed; // nodos ya evaluados

//inserto el primero con f = h (g = 0 en el origen)
int f = this->hValue(dest);
this->parent = nullptr; //padre a null, es el origen
open.insert(std::pair<char,Tile>(f, *this)); //iserto en open


while (!open.empty()){//mientras al lista no este vacia
	//saco la primera casilla del open list (la de menor f);
	Tile q = open.begin()->second;

	//consigo la lista de casilleros adyacentes (a lo sumo 4, si no me muevo en diagonal)
	//necesito info del mapa
	//hay que setear el parent de los adyacentes a q 
	//habria que chequear que adyacentes estan bloqueados y descartarlos !!!
	std::vector<Tile> ady;
	
	//para todos los adyacentes
	
	for (auto it = ady.begin(); it != ady.end(); ++it){
		// si el sucesor es el destino ya esta
		if (it->isEqual(dest)){
			//code
			break;
		}
		//saco el f del sucesor
		//de q al sucesor hay un solo mov, entonces g(sucesor) = g(q) + 1
		int f = q.gValue() + 1 + it->hValue(dest);
		
		//chequear si el suceso esta en closed u open
		//hacer magia
	}
	
	//inserto q en closed, y lo borro de open
	int f = q.hValue(dest);
	closed.insert(std::pair<char,Tile>(f, q));
	open.erase(f);

}
return 0;
}

