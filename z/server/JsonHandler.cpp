#include <fstream>
#include <iostream>
#include "JsonHandler.h"
#include "json.h"

JsonHandler::JsonHandler() {}


void JsonHandler::toJson(std::vector<int> descriptorVector) {

    std::ofstream jsonFile("server/maps/map.json");

    Json::Value vec(Json::arrayValue);

    for (int i = 0; i <descriptorVector.size() ; ++i) {
        vec.append(Json::Value(descriptorVector[i]));
    }

    Json::StyledWriter writer;
    jsonFile << writer.write(vec);
    jsonFile.close();
}

std::vector<int> JsonHandler::jsonToMap() {
    std::vector<int> mapDescriptor;
    std::ifstream jsonFile("server/maps/map.json");

    Json::Reader reader;
    Json::Value root;

    if(!reader.parse(jsonFile, root)) {
        std::cout << reader.getFormattedErrorMessages();
        exit(1);
    } else {
        for (int i = 0; i <root.size() ; ++i) {
            mapDescriptor.push_back(root[i].asInt());
        }
    }

    return mapDescriptor;
}
