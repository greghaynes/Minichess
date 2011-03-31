#ifndef BOARD_GENERATOR_H
#define BOARD_GENERATOR_H

#include "board.h"

class BoardGenerator
{

	public:
		static Board *fromString(const char *str);

};

#endif

