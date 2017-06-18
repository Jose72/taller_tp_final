#ifndef GENMAP_JSONHANDLER_H
#define GENMAP_JSONHANDLER_H


#include <vector>
#include <map>
#include "unitBuilder.h"

class JsonHandler {

public:
    JsonHandler();
    std::vector<int> jsonToMap();
    void jsonToUnits(int &unit_counter,unitBuilder &builder, std::map<int, unit*> &units);

};

#endif //GENMAP_JSONHANDLER_H
