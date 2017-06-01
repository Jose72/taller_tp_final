#include <stdio.h>
#include <iostream>
#include "gameMap.h"
#include "tile.h"
#include "terrain.h"
#include "actualizeUnit.h"

#include "testS.h" //small tests

#include <stdio.h>
#include "server.h"
#include <iostream>

int main(int argc, char **argv)
{
	//test_move_unit();
	
	char c = '0';
	tServer server(atoi(argv[1]));
	server.start();
	while(c != 'q'){
		std::cin.get(c);
	}
	server.stop();
	server.join();
	
	return 0;
	

}