#include "gameList.h"
#include "../common/Lock.h"
#include <iostream>


gameList::gameList(){}

void gameList::push_back(juego* j){
	tLock l(m);
	juegos.push_back(j);
}

size_t gameList::size(){
	tLock l(m);
	return juegos.size();
}

void gameList::stopGames(){
	tLock l(m);
	for (auto it = juegos.begin(); it != juegos.end(); ++it){
		(*it)->stop();
	}
}


bool gameList::gameIsFull(int g_id){
	tLock l(m);
	for (auto it = juegos.begin(); it != juegos.end(); ++it){
		if ((*it)->isCreator(g_id)){
			return ((*it)->isFull());
		}
	}
	return true;
}

void gameList::cleanGames(){
	tLock l(m);
	for (auto it = juegos.begin(); it != juegos.end(); ++it){
		//std::cout << "clean game" << std::endl;
		//si el juego empezo hay que joinear
		if ((*it)->gameStarted()) (*it)->join();
		delete (*it);
	}
}


//id del cliente a unirse
//socket del cliente
//puntero al juego (es el del clientManager para guardarselo)
//id del creador para identificar el juego correspondiente
int gameList::joinGame(int my_id, tSocket *s, juego **j, int creator, int team){
	tLock l(m);
	for (auto it = juegos.begin(); it != juegos.end(); ++it){
		//si es el juego que pedi
		if ((*it)->isCreator(creator)){
			//si me pude unir
			if ((*it)->clientJoin(my_id, s, team) == 0){
				//el manager se guarda el puntero al juego
				*j = (*it);
				return 0;
			}
		}
	}
	return 1;
}

//quiero que sea atomico
//vector de enteros con las caracteristicas del juego
//tamanio del juego
void gameList::descriptionGames(std::vector<int> &des, int &c){
	tLock l(m);
	c = juegos.size();
	for (auto it = juegos.begin(); it != juegos.end(); ++it){
		int a,b,c,d,e;
		(*it)->getDescription(a,b,c,d,e);
		des.push_back(a);
		des.push_back(b);
		des.push_back(c);
		des.push_back(d);
		des.push_back(e);
	}
}