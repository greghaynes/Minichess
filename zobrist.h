#ifndef ZOBRIST_H
#define ZOBRIST_H

#include <stdint.h>

#include "board.h"
#include "boardslot.h"

class Zobrist
{

	public:
		static void key(const BoardSlot &slot,
	                Location location,
	                uint64_t &key);

};

#endif

