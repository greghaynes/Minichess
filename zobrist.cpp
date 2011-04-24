#include "zobrist.h"
#include "randnums.h"

#include <sys/time.h>
#include <stdlib.h>

Zobrist::Zobrist()
{
}

void Zobrist::key(const BoardSlot &slot,
                  Location location,
                  uint64_t &key) const
{
	int type_ndx = 0;
	if(slot.owner()==Player::Player2)
		type_ndx = slot.piece() + 6;
	else
		type_ndx = slot.piece();

	key ^= randnums[location.x()][location.y()][type_ndx];
}

