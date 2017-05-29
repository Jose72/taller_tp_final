#ifndef EVENT_H
#define EVENT_H

class Event {
	private:
		int op_code;
		int unit_game_id;
		int x;
		int y;
	public:
		Event(int op, int u_id, int x, int y);
		int getX();
		int getY();
		int getId();
};


#endif

