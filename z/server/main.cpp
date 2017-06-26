#include <stdio.h>
#include <iostream>
#include "testS.h" //small tests
#include "server.h"
#include "configParser.h"


int main(int argc, char **argv)
{
	if (argc < 1) {
		std::cout << "No hay parametros" << std::endl;
		return -1;
	}
	
	std::ifstream con_file;
	con_file.open(argv[1]);
	if (!con_file.is_open()) return -1;
	configParser cp(con_file);
	int port;
	std::string map_folder;
	std::string unit_info_path;
	cp.parse(port, map_folder, unit_info_path);
	con_file.close();
	
	std::cout << port << std::endl;
	std::cout << map_folder << std::endl;
	std::cout << unit_info_path << std::endl;
	
	
	
	tServer server(port, map_folder, unit_info_path);
	
	char c = '0';
	server.start();
	while(c != 'q'){
		std::cin.get(c);
	}
	server.stop();
	server.join();
	
	return 0;

}