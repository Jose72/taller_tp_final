#include "Units_Protected.h"
#include "../common/Lock.h"

Units_Protected::Units_Protected(std::vector<Unit *> &units): units(units){}

Units_Protected::~Units_Protected() {}

void Units_Protected::add(Unit *unit) {
    tLock(this->mut);
    units.push_back(unit);
}

Unit* Units_Protected::operator[](int i) {
    tLock(this->mut);
    return units[i];
}

int Units_Protected::size() {
    tLock(this->mut);
    return units.size();
}