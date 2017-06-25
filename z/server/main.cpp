#include <stdio.h>
#include <iostream>
#include "testS.h" //small tests
#include "server.h"


int main(int argc, char **argv)
{
	//test_load_u_data();
	
	char c = '0';
	if (argc < 1) {
		std::cout << "No hay parametros" << std::endl;
		return -1;
	}
	tServer server(atoi(argv[1]));
	server.start();
	while(c != 'q'){
		std::cin.get(c);
	}
	server.stop();
	server.join();
	
	return 0;

}