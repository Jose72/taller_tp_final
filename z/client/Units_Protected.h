#ifndef CLIENT_UNITS_PROTECTED_H
#define CLIENT_UNITS_PROTECTED_H


#include <mutex>
#include "Unit.h"
#include "Factory_Units.h"
#include "../common/constants.h"
#include "SoundManager.h"

enum Action{
    DRIVE,
    ATTACK,
    MOVE
};

class Units_Protected {
private:
    std::mutex mut;
    std::map<int, Unit*> &units_map;

public:
    Units_Protected(std::map<int, Unit*> &um);
    ~Units_Protected();
    void add(int cod_u, Unit* unit);
    void animate(int limitXL, int limitXR, int limitYU, int limitYD, SDL_Rect cameraRect,SoundManager &soundManager);
    Unit* selectUnit(int dx1, int dx2, int dy1, int dy2, bool &found, int id_client);
    Unit* selectEnemy(int dx1, int dx2, int dy1, int dy2,Action &action, int id_client);
    bool createIfDoesNotExist(int cod_unit, int unit_type, int unit_owner, int posX, int posY, Factory_Units &factory);
    void cleanDeadUnits();
    Unit* operator [](int i);
    void endGame(int winner);
    int size();
    void setStateUnit(int unitCode, State state);
    void setHealthUnit(int unitCode, int health);
    void setPosUnit(int unitCode, int posX,int posY);
    void setAttackUnit(int unitCode, int posX, int posY);
    void setOwnerUnit(int unitCode, int owner);
    int getOwnerUnit(int unitCode);
    int getHealthUnit(int unitCode);

private:
    void createUnit(int cod_unit,int unit_owner,int posX, int posY, Factory_Units &factory,
                    FlagsUnitType blue, FlagsUnitType green, FlagsUnitType red, FlagsUnitType yellow);

    void createVehicle(int cod_unit,int unit_owner,int posX, int posY,
                       Factory_Units &factory,
                       FlagsUnitType blue,
                       FlagsUnitType green,
                       FlagsUnitType red,
                       FlagsUnitType yellow,
                       FlagsUnitType empty);



};


#endif //CLIENT_UNITS_PROTECTED_H
