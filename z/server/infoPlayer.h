#ifndef INFOPLAYER_H
#define INFOPLAYER_H

#include <vector>
#include <map>
#include "unit.h"

#define MAX_UNITS 50
#define OK 0
#define DEFEAT 1

#define DEATHMATCH 0
#define TEAM_GAME 1

class infoPlayer {
	private:
		int player_id;
		int units_count;
		unit *fort;
		std::vector<int> allies;
		int current_tech_lvl;
		int state;
	public:
		infoPlayer(int id, std::vector<int> allies);
		infoPlayer(int id);
		int getPlayerId();
		int getCurrentTechLvl();
		void incrementTechLvl();
		void decrementTechLvl();
		void getAllies(std::vector<int> &a);
		bool maxUnitsReached();
		void incrementUnitsCount();
		void decrementUnitsCount();
		bool fortAlive();
		void initialize(unit *fort,int units_count);
		int checkVictoryConditions();
};

class infoPlayers{
	private:
		unsigned int max_players;
		int game_type;
		int teams_count;
		std::map<int,infoPlayer> players_info;
	public:
		infoPlayers(int max_p, int game_type, int teams);
		void initializePlayer(int id_p, unit *fort, int units_count);
		void addNewPlayer(int id);
		void updateTechLevels(int id_old, int id_new);
		int checkVictoryConditions(int id_p);
		int getPlayerTechLevel(int id_p);
		void incrementUnitsCount(int id_p);
		void decrementUnitsCount(int id_p);
};



#endif
