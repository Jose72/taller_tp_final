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
		int state;
		
	public:
		infoPlayer(int id, serverProtocol *prot);
		infoPlayer(int id); //no usar
		int getPlayerId();
		bool maxUnitsReached();
		void incrementUnitsCount();
		void decrementUnitsCount();
		int updateVictoryConditions();
		bool isDefeated();
		void sendTeamNumber(int t);
};


#endif
