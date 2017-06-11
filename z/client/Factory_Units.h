#ifndef CLIENT_FACTORY_UNITS_H
#define CLIENT_FACTORY_UNITS_H

#include "SpritesPool.h"
#include "Unit.h"


class Factory_Units {
private:

    SpritesPool &pool;

public:
    Factory_Units(SpritesPool &pool);
    Unit* createUnit(FlagsUnitType unit,int unit_code, int posx, int posy, int unit_owner);

};


#endif //CLIENT_FACTORY_UNITS_H
