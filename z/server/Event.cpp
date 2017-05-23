#include "Event.h"

Event::Event(int op, int x, int y): op_code(op), x(x), y(y) {};


int Event::takeX(){
	return x;
}

int Event::takeY(){
	return y;
}