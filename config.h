#ifndef CONFIG_H
#define CONFIG_H

#define CFG_BOARD_WIDTH      5
#define CFG_BOARD_HEIGHT     6

#define PRINT_MOVES          1

#define NUM_GAMES            1

namespace Piece
{
	enum Type
	{
		None,
		Pawn,
		Rook,
		Knight,
		Bishop,
		Queen,
		King
	};
}

#endif

