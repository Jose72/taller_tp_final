#ifndef Z_MAPLOADER_H
#define Z_MAPLOADER_H


#include "unit.h"
#include "gameMap.h"
#include "JsonHandler.h"

//loadListData carga toda la data de todos los mapas
//String mapName
// cantEquipos del mapa
//dimensiones del mapa
//las 3 se mandan al usuario
//mapsForTeam genera la lista para enviar segun la cantidad de equipos
//loadMap la idea es que cargue las unidades y el descriptor recibiendo el mapName que recibiria el server

class MapLoader {
private:
    JsonHandler &jsonHandler;
    std::map<int, unit*> &unitsVector;
    gameMap &map;
    std::vector<dataMap> &dataMaps;

public:
    MapLoader(JsonHandler &json,
              std::map<int, unit*> &unitsVector,
              gameMap &map,
              std::vector<dataMap> &data);


    void loadListData();
    std::vector<dataMap> mapsForTeams(int cantEquipos);
    void loadMap(std::string mapName);

private:

    void loadDirectory(std::string path);


};


#endif //Z_MAPLOADER_H
