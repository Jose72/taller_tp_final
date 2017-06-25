#ifndef Z_MAPLOADER_H
#define Z_MAPLOADER_H


#include "unit.h"
#include "gameMap.h"
#include "JsonHandler.h"

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

private:

    void loadDirectory(std::string path);


};


#endif //Z_MAPLOADER_H
