#include "actualizeUnit.h"
#include <vector>
#include "tilesListCost.h"
#include <iostream>
#include <math.h>  
#include <algorithm> 

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
//std::cout << "empieza while" << std::endl;
while (!open.empty()){//mientras al lista no este vacia
	//saco la primera casilla del open list (la de menor f);
	
	tile *q = open.begin();
	//std::cout << "current" << std::endl;
	//q->printTile();
	
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
	//last->printTile();
	path.push_back(last);
	last = last->getParent();
}

return 0;
}



int autoAttackActualize(unit &attacker, std::map<int, unit*> &units, gameMap &mapa, double time){
	//si el atacante se mueve no hay autoataque
	if (attacker.isMoving()) return 1;
	//recorro el vect de unidades
	for (auto it = units.begin(); it != units.end(); ++it){
		unit *target = it->second;
		//chequeo quien es el dueño de la unidad
		if (target->isEnemy(attacker)){
			//si esta en rango
			if (attacker.isInRange(*target)){
			
				target->takeDamage(round(attacker.getDamage()));
				//le pego y ya, no sigo con los demas
				return 0;
				
				// en vez de esto se podria setear la unidad como target
				// con un booleano que indique autoataque
				// y que la actualizacion de ataque haga el resto
			
			}
		
		
		}
	}
	
	return 0;
}
/*
int createActualize(unit &u, std::map<int, unit*> &units, gameMap &mapa, double time, int &unit_id_count){
	int new_u_code = u.checkCreating(time);
	if (new_u_code != -1){
		unit *n_u = new unit(u.getOwner(), new_u_code, u.getDestX(), u.getDestY());
		units.insert(std::pair<int,unit*>(unit_id_count, n_u));
		unit_id_count++;
		std::cout << "new unit" <<std::endl;
	}
	return 0;
}
*/
int actualizeUnit::operator()(int unit_game_id, unit &u, std::map<int, unit*> &units, gameMap &mapa, double time, int &unit_id_count, std::set<int> &dead_unit, std::set<int> &actualized_units){
	//std::cout << "pasada---------------------------------------" << std::endl;
	
	std::cout << "start actu-----------" << std::endl;
	int state = u.getState();
	switch(state){
		case MOVING:
			std::cout << "move" << std::endl;
			move_h.moveActualize(u, mapa, 1);
			return 0;
		case ATTACKING:
			std::cout << "attac" << std::endl;
			attack_h.attackActualize(u, units, unit_id_count, time);
			return 0;
	}
	
	/*
	//pendiente: chequear la cant de unidades antes de crear
	
	if (u.isCreating()){ 
		createActualize(u, units, mapa, time, unit_id_count);
	}
	*/
	std::cout << "end actu---------" << std::endl;
	return 0;
}

