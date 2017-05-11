

#include "pathfinder.h"





//hay que ver que tipo de unidad es para ver si puede pasar por determinadas casillas !!!!

//buscar el mejor camino a la casilla destino
int a_start(tile &orig, tile &dest, gameMap &gmap, int unit_code, std::vector<tile> &path){
//necesitaria referencia al mapa??


//se ordena con el f, seria una especie de costo por moverse
//cada casilla tiene uno, lo uso para buscar el camino hasta el destino
//f = g + h
//g = costo por moverme desde el origen hasta la casilla actual, por el camino elegido hasta el momento
//h = costo por moverme desde la casilla actual hasta el destino (se aproxima en gral)


//usar punteros para los sets, sino se rompe todo
//nodos visitados, pero no expandidos
tilesListCost open;
//nodos visitados, y expandidos
tilesListCost closed; // nodos ya evaluados

//inserto, seteo g y h (g = 0 en el origen)
orig.setG(0);
orig.setH(dest);
orig.setParent(nullptr); //padre a null, es el origen
open.insert(orig); //inserto en open
tile *last;

while (!open.empty()){//mientras al lista no este vacia
	//saco la primera casilla del open list (la de menor f);
	
	tile q = open.begin();
	
	// si el actual es el destino ya esta
	if (q.isEqual(dest)){
			last = &q;
			break;
	}
	
	//lo borro de open y lo iserto el closed
	open.eraseIfFound(q);
	closed.insert(q);
		
	//consigo la lista de casilleros adyacentes (maximo 8)
	//necesito info del mapa
	//hay que setear el parent de los adyacentes a q 
	//habria que chequear que adyacentes estan bloqueados y descartarlos !!!
	std::vector<tile> ady;
	gmap.getNeightboors(q, ady);
	//para todos los adyacentes
	for (auto it = ady.begin(); it != ady.end(); ++it){
		//si no se puede pasar por la casilla no hago nada
		if (!it->isPassable(unit_code)) continue;
		
		//seteo de padre a q
		it->setParent(&q);
		

		if (!closed.found(*it)){
			//saco g y h
			it->setG(q.gValue() + q.dist(*it)); 
			it->setH(dest);
			
			//si el sucesor no esta en open agrego
			//si esta, pero este es mejor (menor f), reemplazo
			open.foundReplaceOrInsert(*it);
		}
		
		//si ya esta en close hay que reemplazar como en open?????
	}
	return false;
}

//hay que retornar la lista de casillas (o la lista de coordenadas mejor)
//usar un stack? (es LIFO)

//voy hacia  atras con parent, y veo cant de movimientos
while (last->getParent() != nullptr){
	path.push_back(*last);
	last = last->getParent();
}
	
return 0;
}

