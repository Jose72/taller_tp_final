#include <fstream>
#include <iostream>
#include "JsonHandler.h"
#include "json.h"
#include "unitBuilder.h"

JsonHandler::JsonHandler(std::string &folderPath): folderPath(folderPath) {}


std::vector<int> JsonHandler::jsonToMap(std::string mapName) {
    std::vector<int> mapDescriptor;
    //std::string motherPath = "server/maps/";
	std::string motherPath = folderPath + "/";
    std::string pointJson = ".json";
    std::string directory = motherPath+mapName+pointJson;
    std::ifstream jsonFile(directory);

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


void JsonHandler::jsonToUnits(int &unit_counter,
                              unitBuilder &builder,
                              std::map<int, unit*> &units,
                              std::string mapName ) {

    //std::string motherPath = "server/maps/units";
	std::string motherPath = folderPath + "/units";
    std::string pointJson = ".json";
    std::string directory = motherPath+mapName+pointJson;
    std::ifstream jsonFIle(directory);

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
			//si es un edificio seteo el tech lvl
			if (unitCode == FORT || unitCode == VEHICLE_FACTORY || unitCode == ROBOT_FACTORY){
				int techLvl = root[i]["techLevel"].asInt();
				u->setTechLvl(techLvl);
			}
            units.insert(std::pair<int,unit*>(unit_counter,u));
            unit_counter++;

        }
    }
}

dataMap JsonHandler::jsonToDataMap(std::string directory) {
    std::ifstream jsonFIle(directory);
    Json::Reader reader;
    Json::Value root;
    std::string mapName1;
    int cantEquipos1;
    int dimentisones1;
    if (!reader.parse(jsonFIle, root)) {
        std::cout << reader.getFormattedErrorMessages();
        exit(1);
    } else {
        mapName1 = root[0]["mapName"].asString();
        cantEquipos1 = root[0]["equipos"].asInt();
        dimentisones1 = root[0]["tamanio"].asInt();
    }
    dataMap data;
    data.mapName = mapName1;
    data.cantEquipos = cantEquipos1;
    data.dimensiones = dimentisones1;

    return data;
}

