#ifndef GAMELIST_H
#define GAMELIST_H

#include <vector>
#include <string>
#include <mutex>

#include "../common/Socket.h"
#include "../common/Thread.h"
#include "../common/Lock.h"
#include "juego.h"

class gameList {
	private:
		std::vector<juego*> juegos;
		std::mutex m;
	public:
		gameList();
		void push_back(juego* j);
		size_t size();
		void stopGames();
		void cleanGames();
		int joinGame(int my_id, tSocket *s, juego **j, int creator, int team);
		void descriptionGames(std::vector<int> &des, int &c);
};

#endif