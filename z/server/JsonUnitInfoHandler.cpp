#include <fstream>
#include <iostream>
#include "json.h"
#include "JsonUnitInfoHandler.h"

JsonUnitInfoHandler::JsonUnitInfoHandler(){}

void JsonUnitInfoHandler::jsonToUnitsInfo(infoUnits &iu){
	//std::ifstream jsonFile("/home/jjjtony/TALLER_TP_FINAL/z/server/unitsInfo/unitsInfo.json");
	std::ifstream jsonFile("server/unitsInfo/unitsInfo.json");

    Json::Reader reader;
    Json::Value root;

    if (!reader.parse(jsonFile, root)) {
        std::cout << reader.getFormattedErrorMessages();
        exit(1);
    } else {
        for (unsigned int i = 0; i < root.size(); ++i) {
			int unit_c = root[i]["unit_id"].asInt();
			int class_c = root[i]["class_id"].asInt();
			int height = root[i]["height"].asInt();
			int width = root[i]["width"].asInt();
			int health = root[i]["health"].asInt();
			int blocking = root[i]["blocking"].asInt(); 
			int speed = root[i]["speed"].asInt();
			int range_u = root[i]["range"].asInt();
			int damage = root[i]["damage"].asInt();
			bool explosive = root[i]["explosive"].asInt();
			int unit_to_c = root[i]["u_to_create"].asInt();
			int fab_time = root[i]["fab_time"].asInt();
			int	shoot_time = root[i]["shoot_freq"].asInt();
			int tech_lvl = root[i]["tech_lvl"].asInt();
			int q_to_fab = root[i]["quant_to_create"].asInt();
			
			unitPlantilla up(unit_c, class_c, height, width, health, blocking, speed, 
			range_u, damage, explosive, fab_time, shoot_time, unit_to_c, tech_lvl, q_to_fab);
			
			iu.addInfo(up);
        }
	}
}