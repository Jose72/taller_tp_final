#ifndef EVENT_H
#define EVENT_H

class Event {
	private:
		int op_code;
		int x;
		int y;
	public:
		Event(int op, int x, int y);
		int takeX();
		int takeY();
};


#endif

