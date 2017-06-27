#ifndef TEAM_H
#define TEAM_H


#include <vector>
#include "infoPlayer.h"
#include "Protocol.h"
#include "unit.h"

#define MAX_UNITS 50

#define OK 0
#define DEFEAT 1

#define DEATHMATCH 0
#define TEAM_GAME 1

#define NO_WINNER 0

class team {
	private:
		int team_n;
		unsigned int max_p;
		int max_units;
		int unit_count;
		int state;
		int captured_territories;
		unit* fort;
		std::vector<infoPlayer> players;
	public:
		team(int team_n, int max_p);
		int addPlayer(int p_id, serverProtocol *prot);
		int getTeamNumber();
		bool isFull();
		bool fortIsAlive();
		bool isDefeated();
		int updateVictoryConditions();
		bool maxUnitsReached();
		void incrementUnitsCount();
		void decrementUnitsCount();
		int getCapturedTer();
		void initialize(unit* forts, int unit_count);
		void setFort(unit *);
		void incrementCapturedTer();
		void decrementCapturedTer();
		void sendTeamNumber();
		void sendInitialPos();
		
};

#endif