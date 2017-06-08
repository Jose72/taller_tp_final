#ifndef INFOPLAYER_H
#define INFOPLAYER_H

#include <vector>
#include "unit.h"

class infoPlayer {
	private:
		int player_id;
		unit *fort;
		std::vector<int> allies;
		int current_tech_lvl;
	public:
		infoPlayer(int id, std::vector<int> allies);
		infoPlayer(int id);
		int getCurrentTechLvl();
		void incrementTechLvl();
		void decrementTechLvl();
		void getAllies(std::vector<int> &a);
};

#endif
