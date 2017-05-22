#include "juego.h"

void juego::stop(){
	tLock l(game_m);//lockeo
	for (auto it = cli_skts.begin(); it != cli_skts.end(); ++it){
		(*it)->shutdown(SHUT_RDWR);
	}
	return;
}

void juego::take_event(Event &e){
	tLock l(game_m);//lockeo
	event_list.push(e);
	return;
}

void juego::run(){
	
	
	///tomo eventos de la cola
	///ejecuto
	
	//mientras los sockets funcionen
	//envio los clientes los cambios
	
	return;
}