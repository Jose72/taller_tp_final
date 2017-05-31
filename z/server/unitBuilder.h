#ifndef UNITBUILDER_H
#define UNITBUILDER_H

#include "unit.h"
#include "constants.h"

class unitBuilder {
	public:
		unit* build(int unit_code, int owner, std::vector<int> &allies, int x, int y);
		
};

#endif