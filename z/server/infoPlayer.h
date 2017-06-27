#ifndef INFOPLAYER_H
#define INFOPLAYER_H

#include <vector>
#include <map>
#include "unit.h"
#include "Protocol.h"

#define MAX_UNITS 50

#define OK 0
#define DEFEAT 1

#define DEATHMATCH 0
#define TEAM_GAME 1

#define NO_WINNER 0


//contiene la info global de un jugador
class infoPlayer {
	private:
		int player_id;
		serverProtocol *prot;
		//int state;
		
	public:
		infoPlayer(int id, serverProtocol *prot);
		int getPlayerId();
		void sendTeamNumber(int t);
		void sendInitialPos(int x, int y);
};


#endif
