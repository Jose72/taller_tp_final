#ifndef INFOGAME_H
#define INFOGAME_H

#include <vector>
#include <map>
#include "unit.h"
#include "Protocol.h"
#include "team.h"

#define MAX_UNITS 50

#define OK 0
#define DEFEAT 1

#define DEATHMATCH 0
#define TEAM_GAME 1

#define NO_WINNER 0



//para manejar la info global de todos los jugadores/equipos
class infoGame{
	private:
		unsigned int max_players;
		unsigned int max_teams;
		int game_type;
		std::map<int,infoPlayer> players_info;
		
		
		//tener vector por cada equipo
		std::vector<team> teams;
	public:
		infoGame(int max_p, int game_type, int teams);
		void initializePlayer(int id_p, unit *fort, int units_count);
		
		void addNewPlayer(int id_p); //no usar
		void addNewPlayer(int id_p, serverProtocol *prot);
		//int updateVictoryConditions(int id_p);
		//void incrementUnitsCount(int id_p);
		//void decrementUnitsCount(int id_p);
		//void sendUpdateTechLvl();
		//bool maxPopulationReached(int id_p);
		//int checkForWinner();
		
		void initializeTeams();
		int addNewPlayer(int id_p, serverProtocol *prot, int team_n);
		int updateVictoryCond(int team_n);
		bool maxPopReached(int team_n);
		void incrementUnitsCount(int team_n);
		void decrementUnitsCount(int team_n);
		int getCapturedTer(int team_n);
		void initializeTeam(int team_n, std::vector<unit*> forts, int unit_count);
		int checkForWinner();
		void updateCapturedTer(int old_owner, int new_owner);
		void sendTeamNumbers();
};

#endif