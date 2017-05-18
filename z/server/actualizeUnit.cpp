#include "actualizeUnit.h"
#include <vector>
#include "tilesListCost.h"
#include <iostream>

//hay que ver que tipo de unidad es para ver si puede pasar por determinadas casillas !!!!

//buscar el mejor camino a la casilla destino
int aStart(tile *orig, tile *dest, gameMap &gmap, int unit_code, std::vector<tile*> &path){
//se ordena con el f, seria una especie de costo por moverse
//cada casilla tiene uno, lo uso para buscar el camino hasta el destino
//f = g + h
//g = costo por moverme desde el origen hasta la casilla actual, por el camino elegido hasta el momento
//h = costo por moverme desde la casilla actual hasta el destino (se aproxima en gral, por ej distancia euclidea)


//usar punteros, sino se rompe todo
//nodos visitados, pero no expandidos (no chequee vecinos)
tilesListCost open;
//nodos visitados, y expandidos (chequee vecinos)
tilesListCost closed; // nodos ya evaluados

//inserto, seteo g y h (g = 0 en el origen)
orig->setG(0);
orig->setH(*dest);
orig->setParent(nullptr); //padre a null, es el origen
open.insert(orig); //inserto en open

tile *last = nullptr;
std::cout << "empieza while" << std::endl;
while (!open.empty()){//mientras al lista no este vacia
	//saco la primera casilla del open list (la de menor f);
	
	tile *q = open.begin();
	std::cout << "current" << std::endl;
	q->printTile();
	
	//si la casilla es el destino se termina el recorrido
	if (q->isEqual(*dest)){
			last = q;
			break;
		}
	
	//consigo la lista de casilleros adyacentes
	std::vector<tile*> ady;
	gmap.getNeightboors(*q, ady);
	
	//para todos los adyacentes
	for (auto it = ady.begin(); it != ady.end(); ++it){
		//si no esta en closed y es pasable
		if (!closed.found(*it) && (*it)->isPassable(unit_code)){
			//seteo de padre a q
			(*it)->setParent(q);
			
			//saco g y h
			//dist() es solo para casilla adyacentes!
			(*it)->setG(q->getG() + q->dist(**it)); 
			(*it)->setH(*dest);
			
			//si el sucesor no esta en open agrego
			//si esta, pero este es mejor (menor f), reemplazo
			open.foundReplaceOrInsert(*it);
		}
		
		//si ya esta en close hay que reemplazar como en open?????
	}
	//borro q de open y lo inserto el closed
	open.eraseIfFound(q);
	closed.insert(q);
}

//hay que retornar la lista de punteros (o la lista de coordenadas mejor)
//usar un stack? (es LIFO)

//voy hacia  atras con parent
while (last != nullptr){
	path.push_back(last);
	last = last->getParent();
}

return 0;
}



void actualizeUnit::run(unit &u, gameMap &mapa){
	int c_id = u.getClassId();
	//muevo la unidad
	//saco casillas origen y destino 
	tile *orig = mapa.getTilePFromUnit(u.getX(), u.getY());
	tile *dest = mapa.getTilePFromUnit(u.getDestX(), u.getDestY());
	std::vector<tile*> camino;
	//corro el astart para obtener el camino
	aStart(orig, dest, mapa, c_id, camino);
	//se tiene que mover hasta el centro de la siguiente casilla
	//que seria la segunda guardada en camino (la primera en el origen)
	tile *closer_tile = camino[1];
	
	if (u.isMoving()){
		switch(c_id) {
			case ROBOT:
				
				break;
			case VEHICLE:
				break;
			default:
				break;
		}
	}
}

