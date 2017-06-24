#ifndef GENMAP_JSONHANDLER_H
#define GENMAP_JSONHANDLER_H


#include <vector>
#include "MapDescriptor.h"

class JsonHandler {

public:
    JsonHandler();
    void toJson(std::vector<int> descriptorVector, std::string nameJson);
    void unitsToJson(std::vector<unit> units, std::string nameJson);
    void dataToJson(std::string mapName, int cantEquipos, std::string nameJson);


};


#endif //GENMAP_JSONHANDLER_H
