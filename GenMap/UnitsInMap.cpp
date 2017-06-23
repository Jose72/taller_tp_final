#include "UnitsInMap.h"

UnitsInMap::UnitsInMap(int code, int x, int y, int owner) {
    this->unitCode = code;
    this->posX = x;
    this->posY = y;
    this->owner = owner;
}

int UnitsInMap::getUnitCode() const {
    return unitCode;
}

void UnitsInMap::setUnitCode(int unitCode) {
    UnitsInMap::unitCode = unitCode;
}

int UnitsInMap::getPosX() const {
    return posX;
}

void UnitsInMap::setPosX(int posX) {
    UnitsInMap::posX = posX;
}

int UnitsInMap::getPosY() const {
    return posY;
}

void UnitsInMap::setPosY(int posY) {
    UnitsInMap::posY = posY;
}

int UnitsInMap::getOwner() const {
    return owner;
}

void UnitsInMap::setOwner(int owner) {
    UnitsInMap::owner = owner;
}
