#include "TechLevelProtected.h"
#include "../common/Lock.h"

TechLevelProtected::TechLevelProtected(int techL) {
    this->techLevel = techL;
}

void TechLevelProtected::setTechLevel(int newLevel) {
    tLock(this->mut);
    this->techLevel = newLevel;
}

int TechLevelProtected::getTechLevel() {
    tLock(this->mut);
    return this->techLevel;
}
