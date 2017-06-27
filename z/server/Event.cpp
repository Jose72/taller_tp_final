#include "Event.h"

Event::Event(int op, int u_id, int x, int y): op_code(op), unit_game_id(u_id), x(x), y(y) {}

Event::Event() {}


int Event::getOpCode(){
	return op_code;
}

int Event::getUnitId(){
	return unit_game_id;
}

int Event::getX(){
	return x;
}

int Event::getY(){
	return y;
}