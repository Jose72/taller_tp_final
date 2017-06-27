#include "configParser.h"

configParser::configParser(std::ifstream &config_file): config_file(config_file){
	
}

int configParser::parse(int &port, std::string &map_folder, std::string &unit_info_path){
	std::string po;
	if (!getline(config_file, po)){
		return 1;
	}
	port = atoi(&po[0u]);
	if (!getline(config_file, map_folder)){
		return 1;
	}
	if (!getline(config_file, unit_info_path)){
		return 1;
	}
	return 0;
}