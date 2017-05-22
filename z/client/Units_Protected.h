#ifndef CLIENT_UNITS_PROTECTED_H
#define CLIENT_UNITS_PROTECTED_H


#include <mutex>
#include "Unit.h"

class Units_Protected {
private:
    std::mutex mut;
    std::vector<Unit*> &units;

public:
    Units_Protected(std::vector<Unit*> &units);
    ~Units_Protected();
    void add(Unit* unit);
    Unit* operator [](int i);
    int size();


};


#endif //CLIENT_UNITS_PROTECTED_H
