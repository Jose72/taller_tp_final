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
		bool flagBelongToTerritory(unit *f);
		void changeOwnership();
};

#endif