#ifndef Z_PROTOCOL_H
#define Z_PROTOCOL_H


#include "../common/Socket.h"
#include "Units_Protected.h"
#include "Game_map.h"
#include "Factory_Units.h"
#include "TechLevelProtected.h"
#include "WinnerProtected.h"
#include "SoundManager.h"

struct mapData{
    std::string mapName;
    int cantEquipos;
    int dimensions;
};

class Protocol {
private:
    tSocket &socket;
    Units_Protected &units;
    Game_map &game_map;
    Factory_Units &factory;
    TechLevelProtected &techLevel;
    WinnerProtected &winner;
    SoundManager &soundManager;

public:
    Protocol(tSocket &s, Units_Protected &u, Game_map &g, Factory_Units &f, TechLevelProtected &tech, WinnerProtected &winner, SoundManager &soundManager);
    ~Protocol();
    void moveUnitCS(int cod_unit, int posX, int posY);
    void attackUnitCS(int cod_unit, int cod_objective);
    void driveUnitCS(int cod_unit, int drive_objetive);
    void create_map();
    std::vector<mapData>receiveMapsInfo();
    void sendMapName(std::string mapName);
    void set_units_game();
    void confirm_server(); // Esto es re turbio pero por ahora lo usamos asi que va al protocolo
    void process_message();
    void translate_message(int update, int unitCode,int unitType,int unitOwner,int health,int posX, int posY);


    void create_unit(int i, int i1);
};


#endif //Z_PROTOCOL_H
