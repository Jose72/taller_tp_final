#include <iostream>
#include "Protocol.h"

#define CODE_MOVE_UNIT 0
#define CODE_ATTACK 1
#define CODE_DRIVE 3
#define CODE_SET_POS 1
#define CODE_SET_ATTACK 2
#define CODE_CREATE_UNIT 2
#define CODE_DIE 5
#define CODE_STAND 6
#define CODE_CHECKING_CAPTURE 8
#define CODE_DESTROYED 10
#define CODE_CHANGE_TECH_LEVEL 35
#define CODE_END_GAME 40
#define CODE_OUTSIDE_MAP -200
#define SIZE_INT 4

enum states {NO_STATE, MOVING, ATTACKING, CREATING, DRIVING, DEAD, STANDING, CAPTURED, CHECKING_CAPTURE,
    DEFEATED, DESTROYED, ERASED, READY_TO_DIE};


Protocol::Protocol(tSocket &s, Units_Protected &u, Game_map &g, Factory_Units &f, TechLevelProtected &tech,WinnerProtected &winner,SoundManager &soundManager):
        socket(s), units(u), game_map(g),factory(f), techLevel(tech),winner(winner), soundManager(soundManager) {}

Protocol::~Protocol() {}



void Protocol::moveUnitCS(int cod_unit, int posX, int posY) {
    std::cout << "cod unit: " << cod_unit << " x: " << posX << " y: " << posY << "\n";
    int CO_to_send = htonl(CODE_MOVE_UNIT);
    int CU_to_send = htonl(cod_unit);
    int PX_to_send = htonl(posX);
    int PY_to_send = htonl((posY));
    socket.send((char*) &CO_to_send,SIZE_INT);
    socket.send((char*) &CU_to_send,SIZE_INT);
    socket.send((char*) &PX_to_send,SIZE_INT);
    socket.send((char*) &PY_to_send,SIZE_INT);
}

void Protocol::attackUnitCS(int cod_unit, int cod_objective) {
    int CO_to_send = htonl(CODE_ATTACK);
    int CU_to_send = htonl(cod_unit);
    int O_to_send = htonl(cod_objective);
    socket.send((char*) &CO_to_send,SIZE_INT);
    socket.send((char*) &CU_to_send,SIZE_INT);
    socket.send((char*) &O_to_send,SIZE_INT);
    socket.send((char*) &O_to_send,SIZE_INT);
}

void Protocol::driveUnitCS(int cod_unit, int drive_objetive) {
    int CO_to_send = htonl(CODE_DRIVE);
    int CU_to_send = htonl(cod_unit);
    int O_to_send = htonl(drive_objetive);
    socket.send((char*) &CO_to_send,SIZE_INT);
    socket.send((char*) &CU_to_send,SIZE_INT);
    socket.send((char*) &O_to_send,SIZE_INT);
    socket.send((char*) &O_to_send,SIZE_INT);

}
void Protocol::create_map() {
    int tamanio_map;
    socket.receive((char*)&tamanio_map,SIZE_INT);
    int tamanio_map_SC = ntohl(tamanio_map);
    //std::cout<< tamanio_map_SC << "\n";
    for (int i = 0; i <tamanio_map_SC ; ++i) {
        int tile;
        socket.receive((char*)&tile,SIZE_INT);
        int tile_SC = ntohl(tile);
        //std::cout<< tile_SC <<"\n";
        game_map.add_tile(tile_SC);
    }
}

void Protocol::set_units_game() {
    int cant_unit;
    socket.receive((char*)&cant_unit,SIZE_INT);
    int cant_unit_SC = ntohl(cant_unit);
    for (int i = 0; i <cant_unit_SC ; ++i) {
        int unit_code_config;
        int unit_code;
        int owner;
        int posX;
        int posY;
        socket.receive((char*)&unit_code,SIZE_INT);
        int unit_code_SC = ntohl(unit_code);
        std::cout<< unit_code_SC << "\n";
        socket.receive((char*)&unit_code_config,SIZE_INT);
        int unit_code_config_SC = ntohl(unit_code_config);
        socket.receive((char*)&owner,SIZE_INT);
        int owner_SC = ntohl(owner);
        socket.receive((char*)&posX,SIZE_INT);
        int posX_SC = ntohl(posX);
        socket.receive((char*)&posY,SIZE_INT);
        int posY_SC = ntohl(posY);

        
        /*
        //tech lvl de edificios
        //en unidades comunes deberia ser ignorado???
        int tl;
        socket.receive((char*)&tl,SIZE_INT);
        int tl_SC = ntohl(tl);
         */


        //AGREGAR SWITCH
        units.createIfDoesNotExist(unit_code_SC,unit_code_config_SC,owner_SC,posX_SC,posY_SC,factory);

    }
}

void Protocol::confirm_server() {
    int confirm = 280;
    int confirm_CS = htonl(confirm);
    socket.send((char*)&confirm_CS,SIZE_INT);
    socket.send((char*)&confirm_CS,SIZE_INT);
}

void Protocol::process_message() {
    int cod_act;
    socket.receive((char*)&cod_act,SIZE_INT);
    int cod_act_SC = ntohl(cod_act);


    int cod_unit;
    socket.receive((char*)&cod_unit,SIZE_INT);
    int cod_unit_SC = ntohl(cod_unit);

    int unit_type;
    socket.receive((char*)&unit_type,SIZE_INT);
    int unit_type_SC = ntohl(unit_type);


    int cod_unit_owner;
    socket.receive((char*)&cod_unit_owner,SIZE_INT);
    int cod_unit_owner_SC = ntohl(cod_unit_owner);

    //salud de la unidad
    int message4;
    socket.receive((char*)&message4,SIZE_INT);
    int message4_SC = ntohl(message4);

    /*
    //seria el porcentage de tiempo que falta para la creacion de la unidad (en edificios)
    //el codigo de unidad del conductor para los vehiculos
    //buscar otro uso para los demas??????
    int message5;
    socket.receive((char*)&message5,SIZE_INT);
    int message5_SC = ntohl(message5);
    */

    int posX;
    socket.receive((char*)&posX,SIZE_INT);
    int posX_SC = ntohl(posX);

    int posY;
    socket.receive((char*)&posY,SIZE_INT);
    int posY_SC = ntohl(posY);

    translate_message(cod_act_SC,
                      cod_unit_SC,
                      unit_type_SC,
                      cod_unit_owner_SC,
                      message4_SC,
                      posX_SC,
                      posY_SC);

}

void Protocol::create_unit(int idCreator, int idCreation) {
    int CO_to_send = htonl(CODE_CREATE_UNIT);
    int idCreator_to_send = htonl(idCreator);
    int idCreation_to_send = htonl(idCreation);
    int extra_to_send = htonl(0);
    socket.send((char*) &CO_to_send,SIZE_INT);
    socket.send((char*) &idCreator_to_send,SIZE_INT);
    socket.send((char*) &idCreation_to_send,SIZE_INT);
    socket.send((char*) &extra_to_send,SIZE_INT);
}

void Protocol::translate_message(int update, int unitCode, int unitType, int unitOwner, int health, int posX,
                                 int posY) {
    if (update == CODE_END_GAME) {
        units.endGame(unitCode);
        winner.setWinner(unitCode);
    } else if (update == CODE_CHANGE_TECH_LEVEL) {
        techLevel.setTechLevel(unitCode);

    } else {
        if(units.createIfDoesNotExist(unitCode, unitType, unitOwner, posX, posY, factory)){
            soundManager.playCreationUnit(unitOwner, unitType);
        }
        if (units[unitCode]->get_state() != DEAD1) {
            switch (update) {
                case MOVING:
                    soundManager.playDamage(unitOwner,unitType,units.getHealthUnit(unitCode),health);
                    units.setStateUnit(unitCode,MOVING1);
                    units.setHealthUnit(unitCode,health);
                    units.setPosUnit(unitCode,posX,posY);
                    break;
                case ATTACKING:
                    units.setAttackUnit(unitCode,posX,posY);
                    units.setStateUnit(unitCode,ATTACKING1);
                    units.setHealthUnit(unitCode,health);
                    break;
                case DEAD:
                    units.setStateUnit(unitCode,DEAD1);
                    break;
                case STANDING:
                    soundManager.playDamage(unitOwner,unitType,units.getHealthUnit(unitCode),health);
                    units.setHealthUnit(unitCode,health);
                    units.setStateUnit(unitCode,DRINKING);
                    units.setPosUnit(unitCode,posX,posY);
                    break;
                case CHECKING_CAPTURE:
                    if(units.getOwnerUnit(unitCode) != unitOwner){
                        soundManager.playCaptureFlag(unitOwner, units.getOwnerUnit(unitCode));
                    }
                    units.setOwnerUnit(unitCode,unitOwner);
                    break;
                case DESTROYED:
                    units.setStateUnit(unitCode,DESTROYED1);
                    break;
                case DRIVING:
                    units.setStateUnit(unitCode,DRINKING);
                    units.setPosUnit(unitCode,posX,posY);
                    break;
                case CREATING:
                    soundManager.playDamage(unitOwner,unitType,units.getHealthUnit(unitCode),health);
                    units.setHealthUnit(unitCode,health);
                    units.setOwnerUnit(unitCode,unitOwner);
                    break;
                case ERASED:
                    units.setPosUnit(unitCode,CODE_OUTSIDE_MAP,CODE_OUTSIDE_MAP);
                    units.setHealthUnit(unitCode,health);
                    units.setStateUnit(unitCode,DEAD1);
                    break;
                case DEFEATED:
                    units.setPosUnit(unitCode,posX,posY);
                    units.setHealthUnit(unitCode,health);
                    units.setStateUnit(unitCode,DRINKING);
                    break;

            }
        }
    }
}

std::vector<mapData> Protocol::receiveMapsInfo() {
    std::vector<mapData> vecMapsData;
    int cantMaps;
    socket.receive((char*) &cantMaps,SIZE_INT);
    int cantMapsSC = ntohl(cantMaps);
    for (int i = 0; i <cantMapsSC ; ++i) {
        mapData data;
        int nameSize;
        socket.receive((char*) &nameSize,SIZE_INT);
        int nameSizeSC = ntohl(nameSize);
        char name [nameSizeSC];
        socket.receive(name,nameSizeSC);
        int dim;
        socket.receive((char*) &dim,SIZE_INT);
        int dimSC = ntohl(dim);
        int equipos;
        socket.receive((char*) &equipos,SIZE_INT);
        int equiposSC = ntohl(equipos);
        std::string nameMap(name);
        data.mapName = nameMap;
        data.dimensions = dimSC;
        data.cantEquipos = equiposSC;
        vecMapsData.push_back(data);
    }
    return vecMapsData;
}

void Protocol::sendMapName(std::string mapName) {
    int name_size = mapName.size();
    int nameSizeCS = htonl(name_size);
    socket.send((char*)&nameSizeCS, SIZE_INT);
    socket.send(&mapName[0u], mapName.size());

}

