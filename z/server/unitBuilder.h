#ifndef UNITBUILDER_H
#define UNITBUILDER_H

#include "unit.h"
#include "../common/constants.h"
#include "infoUnits.h"

class unitBuilder {
	private:
		infoUnits &u_info;
	public:
		unitBuilder(infoUnits &u_info);
		unit* build(int unit_code, int owner, int x, int y);
		unit* build(int unit_code, int x, int y);
		
};

#endif