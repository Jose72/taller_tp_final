#ifndef DEFEATHANDLER_H
#define DEFEATHANDLER_H

#include "unit.h"
#include <map>
#include "infoGame.h"

class defeatHandler{
	private:
		int defeatBuilding(unit *u);
		int defeatCommon(unit *u);
		
	public:
		int defeatPlayer(int t_code, std::map<int, unit*> &units);
};

#endif