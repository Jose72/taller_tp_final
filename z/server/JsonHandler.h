#ifndef GENMAP_JSONHANDLER_H
#define GENMAP_JSONHANDLER_H


#include <vector>
#include <map>
#include "unitBuilder.h"

struct dataMap{
    std::string mapName;
    int cantEquipos;
    int dimensiones;
};

class JsonHandler {

public:
    JsonHandler();
    std::vector<int> jsonToMap();
    void jsonToUnits(int &unit_counter,unitBuilder &builder, std::map<int, unit*> &units);
    dataMap jsonToDataMap(std::string directory);

};

#endif //GENMAP_JSONHANDLER_H
