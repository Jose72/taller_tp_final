#include <fstream>
#include <iostream>
#include "JsonHandler.h"
#include "json.h"
#include "unitBuilder.h"

JsonHandler::JsonHandler() {}


std::vector<int> JsonHandler::jsonToMap() {
    std::vector<int> mapDescriptor;
    std::ifstream jsonFile("server/maps/map.json");

    Json::Reader reader;
    Json::Value root;

    if(!reader.parse(jsonFile, root)) {
        std::cout << reader.getFormattedErrorMessages();
        exit(1);
    } else {
        for (unsigned int i = 0; i <root.size() ; ++i) {
            mapDescriptor.push_back(root[i].asInt());
        }
    }

    return mapDescriptor;
}


void JsonHandler::jsonToUnits(int &unit_counter, unitBuilder &builder, std::map<int, unit*> &units ) {
    std::ifstream jsonFIle("server/maps/unitsMap.json");

    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(jsonFIle, root)) {
        std::cout << reader.getFormattedErrorMessages();
        exit(1);
    } else {
        for (unsigned int i = 0; i < root.size(); ++i) {
            int unitCode = root[i]["id"].asInt();
            int posX = root[i]["posX"].asInt();
            int posY = root[i]["posY"].asInt();
            int owner = root[i]["owner"].asInt();
            unit *u = builder.build(unitCode,owner,posX,posY);
            units.insert(std::pair<int,unit*>(unit_counter,u));
            unit_counter++;

        }
    }
}