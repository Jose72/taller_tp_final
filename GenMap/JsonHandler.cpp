#include <fstream>
#include <iostream>
#include "JsonHandler.h"
#include "json.h"

JsonHandler::JsonHandler() {}


void JsonHandler::toJson(std::vector<int> descriptorVector, std::string nameJson) {
    std::ofstream jsonFile(nameJson);

    Json::Value vec(Json::arrayValue);

    for (unsigned int i = 0; i <descriptorVector.size() ; ++i) {
        vec.append(Json::Value(descriptorVector[i]));
    }

    Json::StyledWriter writer;
    jsonFile << writer.write(vec);
    jsonFile.close();
}

void JsonHandler::unitsToJson(std::vector<unit> units, std::string nameJson) {
    std::ofstream jsonFile(nameJson);

    Json::Value unitsJ(Json::arrayValue);
    for(unsigned int i = 0; i < units.size(); i++)
    {
        Json::Value unit;
        unit["id"] = Json::Value(units[i].id);
        unit["posX"] = Json::Value(units[i].posX);
        unit["posY"] = Json::Value(units[i].posY);
        unit["owner"] = Json::Value(units[i].owner);
        unit["techLevel"] = Json::Value(units[i].techLevel);
        unitsJ.append(unit);
    }

    Json::StyledWriter writer;
    jsonFile << writer.write(unitsJ);
    jsonFile.close();
}

void JsonHandler::dataToJson(std::string mapName, int cantEquipos, std::string nameJson) {
    std::ofstream jsonFile(nameJson);
    Json::StyledWriter writer;
    jsonFile << writer.write(Json::Value(mapName));
    jsonFile << writer.write(Json::Value(cantEquipos));
    jsonFile.close();

}

