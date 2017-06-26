#ifndef JSONUNITINFOHANDLER_H
#define JSONUNITINFOHANDLER_H


#include <vector>
#include <map>
#include "unit.h"
#include "infoUnits.h"

class JsonUnitInfoHandler {

public:
    JsonUnitInfoHandler();
    void jsonToUnitsInfo(std::string &file_path, infoUnits &iu);

};

#endif