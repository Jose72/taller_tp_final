#ifndef CAPTUREHANDLER_H
#define CAPTUREHANDLER_H

#include "unit.h"
#include <map>
#include "infoGame.h"

class captureHandler{
	private:
		void captureActualize(int old_owner, int new_owner, std::map<int, unit*> &units, infoGame &ip);
	public:
		void checkingCaptureActualize(unit &u, std::map<int, unit*> &units, int time, infoGame &ip);
		
};

#endif