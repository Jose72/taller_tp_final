#include <fstream>
#include <iostream>
#include "json.h"
#include "JsonUnitInfoHandler.h"

JsonUnitInfoHandler::JsonUnitInfoHandler(){}

void JsonUnitInfoHandler::jsonToUnitsInfo(){
	std::ifstream jsonFile("server/unitsInfo/unitsInfo.json");

    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(jsonFile, root)) {
        std::cout << reader.getFormattedErrorMessages();
        exit(1);
    } else {
        for (unsigned int i = 0; i < root.size(); ++i) {
			/*
            int unitCode = root[i]["unit_id"].asInt();
			int unitClass = root[i]["unit_class"].asInt();
			*/
        }
	}
}