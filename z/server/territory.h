#ifndef TERRITORY_H
#define TERRITORY_H


#include <vector>
#include "unit.h"

class territory {
	private:
		unit *flag;
		std::vector<unit*> factories;
	public:
		territory(unit *f, std::vector<unit*> &facts);
		bool flagBelongToTerritory(unit *f);
		void changeOwnership();
};

#endif