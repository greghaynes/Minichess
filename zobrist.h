#ifndef ZOBRIST_H
#define ZOBRIST_H

#include <stdint.h>

#include "board.h"
#include "boardslot.h"

class Zobrist
{

	public:
		Zobrist();

		void key(const BoardSlot &slot,
		         Location location,
		         uint64_t &key) const;

};

#endif

