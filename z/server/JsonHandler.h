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
    std::vector<int> jsonToMap(std::string mapName);
    void jsonToUnits(int &unit_counter,
                     unitBuilder &builder,
                     std::map<int, unit*> &units,
                     std::string mapName);
    dataMap jsonToDataMap(std::string directory);

};

#endif //GENMAP_JSONHANDLER_H
