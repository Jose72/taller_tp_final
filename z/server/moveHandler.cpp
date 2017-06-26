
#include "moveHandler.h"
#include <vector>
#include "tilesListCost.h"
#include <iostream>
#include <math.h>  
#include <algorithm> 

//hay que ver que tipo de unidad es para ver si puede pasar por determinadas casillas !!!!

//buscar el mejor camino a la casilla destino
int a_Start(tile *orig, tile *dest, gameMap &gmap, int unit_code, std::vector<tile*> &path){
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
	
	//borro q de open y lo inserto el closed
	open.eraseIfFound(q);
	closed.insert(q);
	
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
			
			
			///////////////////////////////////////////////////
			int new_g = q->getG() + q->dist(**it);
			if (open.found((*it))){
				//si el g nuevo es mejor, reemplzo
				if (new_g < (*it)->getG()){
					(*it)->setParent(q);
					(*it)->setG(new_g); 
				} 
			} else {
				//si no estaba en open inserto
				(*it)->setParent(q);
				(*it)->setG(new_g); 
				(*it)->setH(*dest);
				open.insert((*it));
			}
			
			
			
			/////////////////////////////////////////////////////////////////
			/*
			//seteo de padre a q
			(*it)->setParent(q);
			
			//saco g y h
			//dist() es solo para casilla adyacentes!
			
			(*it)->setG(); 
			(*it)->setH(*dest);
			//si el sucesor no esta en open agrego
			//si esta, pero este es mejor (menor f), reemplazo
			open.foundReplaceOrInsert(*it);
			*/
		}
		
	}
	
}

//si se me acabaron los open
//salgo, no hay camino

//hay que retornar la lista de punteros

//std::cout << "last: " << last << std::endl;

//voy hacia  atras con parent
while (last != nullptr){
	//last->printTile();
	path.push_back(last);
	last = last->getParent();
}

return 0;
}


tile* getClosestPassableTile(tile* dest, gameMap &gmap, int c_code){
	std::vector<tile*> ady;
	gmap.getNeightboors(*dest, ady);
	for (auto it = ady.begin(); it != ady.end(); ++it){
		tile *t = (*it);
		if (t->isPassable(c_code)){
			return t;
		}
	}
	return nullptr;
}


//correccion de camino
//en el caso de que se mueva en diagonal y alguna de las 2 casillas que son
//adyacentes a ambas sea bloqueante hayq ue hacer una correccion
void correctPath(gameMap &mapa, int c_code ,std::vector<tile*> &path){
	std::vector<tile*> path_aux;
	int s = path.size();
	if (s < 1) return;
	path_aux.push_back(path[0]);
	for (int i = 1; i < s; ++i){
		tile *t_ant = path[i-1];
		tile *t_next = path[i];
		
		if (t_ant->isDiagonal(*t_next)){
			int dir_x = t_next->getX() - t_ant->getX();
			int dir_y = t_next->getY() - t_ant->getY();
			tile *t1 = mapa.getTileP(t_ant->getX() + dir_x, t_ant->getY());
			tile *t2 = mapa.getTileP(t_ant->getX(), t_ant->getY() + dir_y);
			if (!t1->isPassable(c_code) && t2->isPassable(c_code)){
				path_aux.push_back(t2);
			} else {
				if (t1->isPassable(c_code) && !t2->isPassable(c_code)){
					path_aux.push_back(t1);
				}
			}
		}
		path_aux.push_back(t_next);
	}
	path = path_aux;
	return;
}


int moveHandler::moveActualize(unit &u, gameMap &mapa, double time){
	int u_class = u.getClassId();
	switch(u_class){
		case ROBOT:
		case VEHICLE:
			return moveCommonActualize(u, mapa, time);
		case BULLET:
			return moveBulletActualize(u, time);
		default:
			return 0;
	}
	
}




int moveHandler::moveCommonActualize(unit &u, gameMap &mapa, double time){
	
		if (u.getClassId() != ROBOT && u.getClassId() != VEHICLE) return 1;
		//necesito clse de unidad
		int c_id = u.getClassId();
		double x_unit = u.getX_D();
		double y_unit = u.getY_D();
		//std::cout << "dest_x: " << u.getDestX() << std::endl;
		//std::cout << "dest_y: " << u.getDestY() << std::endl;
		//saco casillas origen y destino 
		tile *orig = mapa.getTilePFromUnit(x_unit, y_unit);
		tile *dest = mapa.getTilePFromUnit(u.getDestX(), u.getDestY());
		//orig->printTile();
		//dest->printTile();
		std::vector<tile*> camino;
		
		//corro el astart para obtener el camino
		a_Start(orig, dest, mapa, c_id, camino);
		
		//se tiene que mover hasta el centro de la siguiente casilla del camino
		//que seria la segunda guardada en camino (la primera en el origen)
		//si no hay mas de 1 es el origen
		//std::cout << camino.size() << std::endl;

		if (camino.size() == 0) {
			//busco camino a la cassila pasable mas cercana
			tile *new_dest = mapa.getClosestPassableTile(dest->getX(), dest->getY(), c_id);

			a_Start(orig, new_dest, mapa, c_id, camino);
			
			if (camino.size() == 0) {
				//si no hay camino 
				//me quedo donde estoy y paso a standing
				u.stop();
				u.changeState(STANDING);
				std::cout << "no camino" << std::endl;
				return 1;
			}
			
			tile *last_tile = camino[0];
			//setea la ultiam casilla del nuevo camino como destino
			u.setDestiny(last_tile->getX()*32+15, last_tile->getY()*32+15);
			/*
			for (auto it = camino.begin(); it != camino.end(); ++it){
				(*it)->printTile();
			}
			*/
		}
		


		//correcion de camino
		correctPath(mapa, c_id, camino);

		//busco la casilla mas cercana del camino
		tile *closer_tile = camino[camino.size() - 1];
		if (camino.size() > 1){
			closer_tile = camino[camino.size() - 2];
		}
		
		
		//conseguir el centro de la casilla (coord pixel)
		int x_closer = 15 + 32 * closer_tile->getX();
		int y_closer = 15 + 32 * closer_tile->getY(); 
		//si hay una sola casilla (estas en la casilla destino)
		//los yx que queres son los de destino
		if (camino.size() == 1){
			x_closer = u.getDestX(); 
			y_closer = u.getDestY();
		}
		
		//std::cout << "x_closer" << x_closer << std::endl;
		//std::cout << "y_closer" << y_closer << std::endl;
		
		//distancia a esa coord (euclidea)
		double dist = sqrt(pow((x_unit - x_closer),2) + pow((y_unit - y_closer),2));
		
		if (dist != 0) { // si no  estoy en el destino
			//seteo velocidad
			//multiplico por el factor de terreno de la casilla actual
			//y por lo demas si es vehiculo
			
			double speed = 0;
			if (c_id == ROBOT){
				speed = std::max(u.getSpeed() * orig->getTerrainFactor(), 1.0);
			}
			if (c_id == VEHICLE){
				speed = std::max(u.getSpeed() * orig->getTerrainFactor() * (1 - u.getRelativeDamage()), 1.0);
			}
			//si es una unidad no movible hay un error
			if (speed == 0) return 1; //no deberia suceder

			//calculo los nuevos xy
			double new_x = x_unit + ((x_closer - x_unit) / dist ) * time * speed;
			double new_y = y_unit + ((y_closer - y_unit) / dist ) * time * speed;
			
			//si la distancia a los xy mas cercanos es mayor
			//a la distancia hacia el destino, seteo el destino como pos
			if (sqrt(pow((u.getDestX() - x_unit),2) + pow((u.getDestY() - y_unit),2)) <= dist){
				u.setPos(u.getDestX(), u.getDestY());
			} else {
				//si la dist de los nuevos xy con la pos de partida es mayor o igual
				//a la de partida con los xy mas cercanos, seteo los mas cercanos como pos actual
				//sino seteo los nuevos xy
				if (sqrt(pow((new_x - x_closer),2) + pow((new_y - y_closer),2)) <= dist){
					u.setPos(new_x, new_y);
				} else {
					u.setPos(x_closer, y_closer);
				}
			}
		}
		//u.printPos();
		
		
		////status check
		if (u.isMoving()){
		//si tengo target
			if (u.getTarget()){
				//si estoy en el rango
				if (u.targetIsInRange()){
					//si es atacable
					if (u.targetIsAttackable()){
						//ataco
						u.changeState(ATTACKING);
						//std::cout << "ataq mov" << std::endl;
					} else{
						//si puedo conducir al target lo ahgo
						if (u.canDriveTarget()){
							u.drive(u.getTarget());
						} else {
							u.stop();
							u.changeState(STANDING);
						}
					}
					
				} else {
					u.moveToTarget();
				}
			} else{
				//std::cout << "sigo mov" << std::endl;
			}
		} else {//si llegue a destino
			u.changeState(STANDING);
		}
		
		return 0;
}

int moveHandler::moveBulletActualize(unit &u, double time){
	double x_unit = u.getX_D();
    double y_unit = u.getY_D();
	int x_dest = u.getDestX();
	int y_dest = u.getDestY();
	double speed = std::max(u.getSpeed(), 1);
	double dist = sqrt(pow((x_unit - x_dest),2) + pow((y_unit - y_dest),2));
	double new_x = x_unit + ((x_dest - x_unit) / dist ) * time * speed;
    double new_y = y_unit + ((y_dest - y_unit) / dist ) * time * speed;
	if (sqrt(pow((new_x - x_dest),2) + pow((new_y - y_dest),2)) < dist){
		u.setPos(new_x, new_y);
	} else {
		u.setPos(x_dest, y_dest);
	}
	
	//status check
	if (!u.isMoving()){
		u.changeState(ATTACKING);
	}
	
	return 0;
}
 