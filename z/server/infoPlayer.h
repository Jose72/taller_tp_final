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
		int units_count;
		unit *fort;
		serverProtocol *prot;
		
		int current_tech_lvl;
		int state;
	public:
		infoPlayer(int id, serverProtocol *prot);
		infoPlayer(int id); //no usar
		int getPlayerId();
		int getCurrentTechLvl();
		void incrementTechLvl();
		void decrementTechLvl();
		bool maxUnitsReached();
		void incrementUnitsCount();
		void decrementUnitsCount();
		bool fortAlive();
		void initialize(unit *fort,int units_count);
		int updateVictoryConditions();
		void sendUpdateTechLvl();
		bool isDefeated();
};



//para manejar la info global de todos los jugadores/equipos
class infoPlayers{
	private:
		unsigned int max_players;
		int game_type;
		int teams_count;
		std::map<int,infoPlayer> players_info;
		//tener vetcore por cada equipo
		std::map<int,infoPlayer> team_1_info;
		std::map<int,infoPlayer> team_2_info;
		std::map<int,infoPlayer> team_3_info;
		std::map<int,infoPlayer> team_4_info;
	public:
		infoPlayers(int max_p, int game_type, int teams);
		void initializePlayer(int id_p, unit *fort, int units_count);
		void addNewPlayer(int id); //no usar
		void addNewPlayer(int id, serverProtocol *prot);
		void updateTechLevels(int id_old, int id_new);
		int updateVictoryConditions(int id_p);
		int getPlayerTechLevel(int id_p);
		void incrementUnitsCount(int id_p);
		void decrementUnitsCount(int id_p);
		void sendUpdateTechLvl();
		bool maxPopulationReached(int id_p);
		int checkForWinner();
};



#endif
