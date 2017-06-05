
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


int moveHandler::moveActualize(unit &u, gameMap &mapa, int time){
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



int moveHandler::moveCommonActualize(unit &u, gameMap &mapa, int time){
	
		if (u.getClassId() != ROBOT && u.getClassId() != VEHICLE) return 1;
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
		a_Start(orig, dest, mapa, c_id, camino);
		
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
		
		
		////status check
		if (u.isMoving()){
		//si tengo target
			if (u.getTarget()){
				//si estoy en el rango
				if (u.targetIsInRange()){
					//si es enemigo
					if (u.targetIsEnemy()){
						//ataco
						u.changeState(ATTACKING);
					} else{
						u.changeState(STANDING);
					}
					
				} else {
					u.moveToTarget();
				}
			} 
		} else {//si llegue a destino
			u.changeState(STANDING);
		}
		
		return 0;
}

int moveHandler::moveBulletActualize(unit &u, int time){
	int x_unit = u.getX();
	int y_unit = u.getY();
	int x_dest = u.getDestX();
	int y_dest = u.getDestY();
	double speed = std::max(u.getSpeed(), 1);
	double dist = sqrt(pow((x_unit - x_dest),2) + pow((y_unit - y_dest),2));
	int new_x = x_unit + ((x_dest - x_unit) / dist ) * time * speed;
	int new_y = y_unit + ((y_dest - y_unit) / dist ) * time * speed;
	if (sqrt(pow((new_x - x_dest),2) + pow((new_y - y_dest),2)) < dist){
		u.setPos(round(new_x), round(new_y));
	} else {
		u.setPos(x_dest, y_dest);
	}
	
	u.printPos();
	//status check
	if (!u.isMoving()){
		u.changeState(ATTACKING);
	}
	
	
	return 0;
 }
 
