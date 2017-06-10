#ifndef CLIENT_UNITS_PROTECTED_H
#define CLIENT_UNITS_PROTECTED_H


#include <mutex>
#include "Unit.h"
#include "Factory_Units.h"

class Units_Protected {
private:
    std::mutex mut;
    std::map<int, Unit*> &units_map;

public:
    Units_Protected(std::map<int, Unit*> &um);
    ~Units_Protected();
    void add(int cod_u, Unit* unit);
    void animate(int limitXL, int limitXR, int limitYU, int limitYD, SDL_Rect cameraRect);
    Unit* selectUnit(int dx1, int dx2, int dy1, int dy2, bool &found);
    void createIsNotExist(int cod_unit, int unit_type,int unit_owner,int posX, int posY, Factory_Units &factory);
    void cleanDeadUnits();
    Unit* operator [](int i);
    int size();


private:
    void createUnit(int cod_unit,int unit_owner,int posX, int posY, Factory_Units &factory,
                    FlagsUnitType blue, FlagsUnitType green, FlagsUnitType red, FlagsUnitType yellow);


};


#endif //CLIENT_UNITS_PROTECTED_H
