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



int moveActualize(unit &u, gameMap &mapa, double time){
	//necesito clse de unidad
		int c_id = u.getClassId();
		int x_unit = u.getX();
		int y_unit = u.getY();
		//saco casillas origen y destino 
		tile *orig = mapa.getTilePFromUnit(x_unit, y_unit);
		tile *dest = mapa.getTilePFromUnit(u.getDestX(), u.getDestY());
		//orig->printTile();
		//dest->printTile();
		std::vector<tile*> camino;
		
		//corro el astart para obtener el camino
		aStart(orig, dest, mapa, c_id, camino);
		
		/*
		std::cout << "camnio" << std::endl;
		for (unsigned int i = 0; i < camino.size(); i++){
			camino[i]->printTile();
		}
		std::cout << "camnio end" << std::endl;
		*/
		
		//se tiene que mover hasta el centro de la siguiente casilla del camino
		//que seria la segunda guardada en camino (la primera en el origen)
		//si no hay mas de 1 es el origen
		//std::cout << camino.size() << std::endl;
		if (camino.size() == 0) return 1;
		tile *closer_tile = camino[camino.size() - 1];
		if (camino.size() > 1){
			closer_tile = camino[camino.size() - 2];
			
		}
		
		//std::cout << "closer tile" << std::endl;
		//closer_tile->printTile();
		
		//conseguir el centro de la casilla (coord pixel)
		int x_closer = 15 + 32 * closer_tile->getX();
		int y_closer = 15 + 32 * closer_tile->getY(); 
		//si hay una sola casilla (estas en la casilla destino)
		//los yx que queres son los de destino, no el centro de la casilla
		if (camino.size() == 1){
			x_closer = u.getDestX(); 
			y_closer = u.getDestY();
		}
		
		//std::cout << "x_closer" << x_closer << std::endl;
		//std::cout << "y_closer" << y_closer << std::endl;
		
		//distancia a esa coord (euclidea)
		double dist = sqrt(pow((x_unit - x_closer),2) + pow((y_unit - y_closer),2));
		//std::cout << x_unit - x_closer << std::endl;
		//std::cout << y_unit - y_closer << std::endl;
		
		if (dist == 0) { //ya estas en el destino
			return 0;
		}
		
		//seteo velocidad
		//multiplico por el factor de terreno de la casilla actual
		//y por 
		double speed = std::max(u.getSpeed() * orig->getTerrainFactor() * (1 - u.getRelativeDamage()), 1.0);
		//si es una unidad no movible hay un error
		if (speed == 0) return 1; //no deberia suceder
		
		//calculo los nuevos xy
		int new_x = x_unit + ((x_closer - x_unit) / dist ) * time * speed;
		int new_y = y_unit + ((y_closer - y_unit) / dist ) * time * speed;
		/*
		std::cout << "time " << time << std::endl;
		std::cout << "speed " << speed << std::endl;
		std::cout << "dist " << dist << std::endl;
		std::cout << "new_x " << new_x << std::endl;
		std::cout << "new_y " << new_y << std::endl;
		*/
		//si la dist de los nuevos xy con el origen es mayor o igual
		//a la del origen on el destno, seteo el destino como pos actual
		//sino seteo los nuevos xy
		
		if (sqrt(pow((new_x - x_closer),2) + pow((new_y - y_closer),2)) < dist){
			u.setPos(round(new_x), round(new_y));
		} else {
			u.setPos(x_closer, y_closer);
		}

		u.printPos();
		return 0;
}

int attackActualize(unit &attacker, double time){
	unit *attacked = attacker.getTarget();
	if (attacker.isInRange(*attacked, attacker.attackRange())){
			//si me estoy moviendo me detengo
			//estaba siguiendo a la unidad para atacar
			if (attacker.isMoving()) {
				//std::cout << "me detuve" << std::endl;
				attacker.stop();
			}
			attacked->takeDamage(round(attacker.getDamage(time)));
		} else {
			//si no estoy en rango, seteo como destino a la unidad
			//el target se puede estar moviendo por eso hay que hacer esto cada vez
			//asi actualizar el destino
			//hay que usar un bool para saber si es auto-ataque y no hacer esto
			//std::cout << "seteo target como destino" << std::endl;
			attacker.move(attacked->getX(), attacked->getY());
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
			if (attacker.isInRange(*target, attacker.attackRange())){
			
				target->takeDamage(round(attacker.getDamage(time)));
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

int actualizeUnit::operator()(unit &u, std::map<int, unit*> &units, gameMap &mapa, double time, int &unit_id_count){
	//std::cout << "pasada---------------------------------------" << std::endl;
	
	if (u.isMoving()) {
		moveActualize(u, mapa, time);
	} 
	
	
	if (u.isAttacking()){
		attackActualize(u, time);
	} else {
		autoAttackActualize(u, units, mapa, time);
	}
	
	//pendiente: chequear la cant de unidades antes de crear
	if (u.isCreating()){ 
		createActualize(u, units, mapa, time, unit_id_count);
	}
	
	
	return 0;
}

