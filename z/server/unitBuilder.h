#ifndef UNITBUILDER_H
#define UNITBUILDER_H

#include "unit.h"
#include "../common/constants.h"

class unitBuilder {
	public:
		unit* build(int unit_code, int owner, int x, int y);
		unit* build(int unit_code, int x, int y);
		
};

#endif