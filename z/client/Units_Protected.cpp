#include "Units_Protected.h"
#include "../common/Lock.h"

Units_Protected::Units_Protected(std::map<int, Unit*> &um): units_map(um){}

Units_Protected::~Units_Protected() {}

void Units_Protected::add(int cod_u, Unit *unit) {
    tLock(this->mut);
    units_map[cod_u]= unit;
}

Unit* Units_Protected::operator[](int i) {
    tLock(this->mut);
    return units_map[i];
}

int Units_Protected::size() {
    tLock(this->mut);
    return units_map.size();
}