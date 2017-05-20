#ifndef TILESLISTCOST_H
#define TILESLISTCOS_H

#include <vector>
#include "tile.h"

#define FOUND_BETTER_G 0
#define NOT_FOUND 1
#define FOUND_WORST_G 2


class tilesListCost{
	private:
		std::vector<tile*> casillas;
	public:
		void insert(tile *t);
		void eraseIfFound(tile *t);
		bool empty();
		bool found(tile *t);
		tile* begin();
		int foundReplaceOrInsert(tile *t);
		int size();
		void print();
};

#endif
