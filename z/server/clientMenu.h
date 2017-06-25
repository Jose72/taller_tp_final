#ifndef CLIENTMENU_H
#define CLIENTMENU_H

#include "../common/Socket.h"
#include "gameList.h"
#include "Protocol.h"
#include "../common/Lock.h"
#include "juego.h"
#include <unistd.h>

#define CREATE_GAME 0
#define JOIN_GAME 1


// NO TERMINADO, NO USAR!!!!!!!!!

class clientMenu {
	private:
		int cli_id;
		tSocket &skt;
		gameList &gl;
		juego *j;
	public:
		clientMenu(int cli_id, tSocket &skt, gameList &gl, juego *j);
		int gameSelection();
};

#endif