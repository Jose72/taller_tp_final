#include "infoPlayer.h"
		
infoPlayer::infoPlayer(int id, std::vector<int> allies): player_id(id), 
allies(allies), current_tech_lvl(1){}

infoPlayer::infoPlayer(int id): player_id(id), current_tech_lvl(1){}

int infoPlayer::getCurrentTechLvl(){
	return current_tech_lvl;
}

void infoPlayer::incrementTechLvl(){
	current_tech_lvl++;
}

void infoPlayer::decrementTechLvl(){
	current_tech_lvl--;
}

void infoPlayer::getAllies(std::vector<int> &a){
	a = allies;
}
