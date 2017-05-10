#include "tile.h"
#include "gameMap.h"
#include <map>
#include <vector>




//buscar el mejor camino a la casilla destino
int moveTo(tile &orig, tile &dest, gameMap &gmap){
//necesitaria referencia al mapa??


//se ordena con el f, seria una especie de costo por moverse
//cada casilla tiene uno, lo uso para buscar el camino hasta el destino
//f = g + h
//g = costo por moverme desde el origen hasta la casilla actual, por el camino elegido hasta el momento
//h = costo por moverme desde la casilla actual hasta el destino (se aproxima en gral)

//nodos visitados, pero no expandidos
std::map<int, tile> open;
//nodos visitados, y expandidos
std::map<int, tile> closed; // nodos ya evaluados

//inserto el primero con f = h (g = 0 en el origen)
int f = orig.hValue(dest);
orig.setParent(nullptr); //padre a null, es el origen
open.insert(std::pair<int, tile>(f, orig)); //inserto en open


while (!open.empty()){//mientras al lista no este vacia
	//saco la primera casilla del open list (la de menor f);
	

	tile q = open.begin()->second;

	//consigo la lista de casilleros adyacentes (maximo 8)
	//necesito info del mapa
	//hay que setear el parent de los adyacentes a q 
	//habria que chequear que adyacentes estan bloqueados y descartarlos !!!
	std::vector<tile> ady;
	
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
	closed.insert(std::pair<int, tile>(f, q));
	open.erase(f);

}
return 0;
}