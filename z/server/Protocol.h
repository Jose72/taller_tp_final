#ifndef SERVERPROTOCOL_H
#define SERVERPROTOCOL_H

#include <vector>
#include <map>
//#include <dataMap>
#include "../common/Socket.h"
#include "unit.h"
#include "Event.h"
#include "JsonHandler.h"

class serverProtocol {
private:
    tSocket &socket;
    //ACA PONE OTRAS COSAS SI LAS NECESITAS

public:
    serverProtocol(tSocket &s);
    ~serverProtocol();

    //SIGO LO QUE ESTA EN EL DOC, COMO LO PROCESAS Y ESO FIJATE VOS

    //ENVIAR
    void send_id_client(int id_client);
    void send_map(int * map_s, unsigned int size);
	void send_map(std::vector<int> &map_s);
    void send_units_game(std::map<int,unit*> &map_units);
	void send_team_number(int t);
	void send_init_pos(int x, int y);
	int sendActualization(std::map<int,unit*> &map_units);
    int receive_event(Event &e);
	int sendVictory(int winner);
	int sendOKConfimation();
	void sendMapsInfo(std::vector<dataMap> &maps);
	void send_map_dim(int map_dim);

	void receiveSelectionCode(int &c);
	void receiveCreateGameData(int &cant_p, int &type_game, int &teams);
	void receiveMapName(std::string &map_name);
	void sendGamesDescription(std::vector<int> &des, int cant_j);
	void receiveGameToJoin(int &g_id, int &t);
};


#endif //Z_PROTOCOL_H
