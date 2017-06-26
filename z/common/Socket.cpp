#include "Socket.h"
#include <sys/socket.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h> 
#include <string.h>


#define LISTEN_MAX 20

tSocket::tSocket() {
	skt = socket(AF_INET, SOCK_STREAM, 0);
	if (skt == -1) {
		std::cout << "tSocket: error create" << std::endl;
		throw 1;}
}

tSocket::tSocket(int fd) {
	skt = fd;
	if (skt == -1) {
		std::cout << "tSocket: error create" << std::endl;
		throw 1;}
}

tSocket::~tSocket() {
	if (skt != -1) {
        ::shutdown(skt, SHUT_RDWR);
        ::close(skt);
        }
}



void tSocket::bindAndListen(int port_number) {
	struct sockaddr_in serv;
	memset((char*)&serv, 0, sizeof(sockaddr_in));
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = INADDR_ANY;
	serv.sin_port = port_number;
	int s;
	s = bind(skt, (struct sockaddr *)&serv, sizeof(serv));
	s = listen(skt, LISTEN_MAX);
	if (s == -1) {
		std::cout << "tSocket: error bindAndListen" << std::endl;
		throw 1;}
}

void tSocket::connect(const char *ip_address, int port_number) {
	struct sockaddr_in serv;
	serv.sin_addr.s_addr = inet_addr(ip_address);
        serv.sin_family = AF_INET;
        serv.sin_port = port_number;
	int s = ::connect(skt , (struct sockaddr *)&serv , sizeof(serv));
	if (s == -1) {
		std::cout << "tSocket: error connect: "<< strerror(errno) << std::endl;
		throw std::runtime_error(strerror(errno));}
}

tSocket tSocket::accept(){
	int skt_ret = ::accept(skt, NULL, NULL);
	if (skt_ret == -1) {
		//std::cout << "tSocket: error accept" << std::endl;
		throw std::runtime_error("Socket error aceptador");}
        tSocket accepted(skt_ret);
        return accepted;
}

int tSocket::send(const char* buffer, size_t length){
	unsigned int bytes_sent = 0;
    while (bytes_sent < length){
        int s = ::send(skt, buffer + bytes_sent, length - bytes_sent, 
		MSG_NOSIGNAL);
        if (s < 0) {
			return s;
        } else {
			if (s == 0) {
				return 0;
			}
            bytes_sent = bytes_sent + s;
        }
    }
    return bytes_sent;
}

int tSocket::receive(char* buffer, size_t length){
    unsigned int bytes_recived = 0;
    while (bytes_recived < length){
        int s = recv(skt, buffer + bytes_recived, length - bytes_recived, 
		MSG_NOSIGNAL);
        if (s < 0) {
			return s;
        } else {
			if (s == 0) {
				return 0;
			}
            bytes_recived = bytes_recived + s;
        }
    }
    return bytes_recived;
}

void tSocket::shutdown(int how){
    if (skt != -1) ::shutdown(skt, how);
    //if (::shutdown(skt, how) == -1) {throw 1;}
}

tSocket::tSocket(tSocket&& other){
	this->skt = other.skt;
	other.skt = -1;
}

tSocket& tSocket::operator=(tSocket&& other){
		this->skt = other.skt;
                other.skt = -1;
		return *this;
}
