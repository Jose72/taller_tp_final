#include "infoPlayer.h"
		
		

infoPlayer::infoPlayer(int id, serverProtocol *prot): player_id(id), prot(prot) {}


void infoPlayer::sendTeamNumber(int t){
	prot->send_team_number(t);
}

void infoPlayer::sendInitialPos(int x, int y){
	prot->send_init_pos(x, y);
}