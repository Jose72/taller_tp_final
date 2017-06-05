#ifndef CAPTUREHANDLER_H
#define CAPTUREHANDLER_H

#include "unit.h"
#include <map>

class captureHandler{
	private:
		void captureActualize(int old_owner, int new_owner, std::map<int, unit*> &units);
	public:
		void checkingCaptureActualize(unit &u, std::map<int, unit*> &units, int time);
		
};

#endif