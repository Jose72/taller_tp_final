#include "clientManager.h"
#include <string>
#include <iostream>
#include <vector>
#include "string.h"
#include <mutex>

tClientManager::tClientManager(tSocket cli_s, std::mutex &manager_m): 
cli_skt(std::move(cli_s)), manager_m(manager_m) {}


//enviar y recibir (protocolo envia size primero, son del tp3) cambiarlos!!!

//tiene que haber dos protocolos:
//antes de empezar la partida y durante el juego

int receiveMessage(tSocket &skt_cli, std::string &msg){
	int s;
	int size_msg = 0;//aux para tamaño 
	s = skt_cli.receive((char *)&size_msg, sizeof(int)); //recivo tam msg
	//Reservo tamaño mensaje
	char* buff = new char [size_msg + 1];
	buff[size_msg]='\0';
	s = skt_cli.receive(buff, size_msg);
	//std::cout << "msg from client: " << buff << std::endl;
	msg = std::string(buff);
	delete [] buff;
	return s;
}	

int sendMessage(tSocket &skt_cli, std::string &msg_to_send){
	int s;
	int size_msg = msg_to_send.size(); //htonl
	//std::cout << "tam msg to send: " << size_msg << std::endl;
	s = skt_cli.send((char*)&size_msg, sizeof(size_msg));
	s = skt_cli.send(&msg_to_send[0u], size_msg);
	return s;
}



void tClientManager::stop(){
        cli_skt.shutdown(SHUT_RDWR);
}

void tClientManager::run(){
	std::string msg;
	
	//primero recibir datos de usuario
	//enviar datos partida
	int map_codes[64] = {0};
	map_codes[15] = 1;
	map_codes[16] = 1;
	map_codes[17] = 1;
	map_codes[18] = 1;
	map_codes[31] = 1;
	map_codes[32] = 1;
	map_codes[33] = 1;
	map_codes[34] = 1;
	map_codes[56] = 2;
	map_codes[57] = 2;
	map_codes[58] = 2;

	cli_skt.send((char*) map_codes, sizeof(int) * 64);

	char bu[512];

	cli_skt.receive(&bu[0], 4);
	std::cout << bu << std::endl;
	
	//send();
	//aca tendria que lanzar la partida !!!!!!
	//que pasa si otro ya la lanzo??
	//bool para saber?
	
	//en la partida se les envia a todos
	//los managers pasan a solo recibir eventos
	//la partida tendria que tener los socket de los clientes
	//mandar puntero al socket??
	
	
	//loop receptor de eventos
	//int s = 1;
	/*
	while (s>0){//mientras socket valido
		
		//recivo eventos del cliente
		
		//guardarlos en la cola de eventos
		
	}
	*/
	return;
}
