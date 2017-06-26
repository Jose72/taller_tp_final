#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H



#include <iostream>
#include <fstream>
#include <string>
#include "infoUnits.h"

class configParser {
		std::ifstream &config_file;
	public:
		configParser(std::ifstream &config_file);
		int parse(int &port, std::string &map_folder, std::string &unit_info_folder);
};

#endif
