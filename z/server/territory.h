#ifndef TERRITORY_H
#define TERRITORY_H


#include <vector>
#include "unit.h"

class territory {
	private:
		unit *flag;
		unit *factory;
	public:
		territory(unit *f, unit *factory);
		void changeOwnership();
};

#endif