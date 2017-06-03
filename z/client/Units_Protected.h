#ifndef CLIENT_UNITS_PROTECTED_H
#define CLIENT_UNITS_PROTECTED_H


#include <mutex>
#include "Unit.h"

class Units_Protected {
private:
    std::mutex mut;
    std::map<int, Unit*> &units_map;

public:
    Units_Protected(std::map<int, Unit*> &um);
    ~Units_Protected();
    void add(int cod_u, Unit* unit);
    Unit* operator [](int i);
    int size();


};


#endif //CLIENT_UNITS_PROTECTED_H
