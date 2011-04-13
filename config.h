#ifndef CONFIG_H
#define CONFIG_H

#define CFG_BOARD_WIDTH      5
#define CFG_BOARD_HEIGHT     6

#define PRINT_MOVES          1

#define NUM_GAMES            1

#define CFG_PIECEVAL_PAWN    1
#define CFG_PIECEVAL_ROOK    6
#define CFG_PIECEVAL_KNIGHT  5
#define CFG_PIECEVAL_BISHOP  5
#define CFG_PIECEVAL_QUEEN   9
#define CFG_PIECEVAL_KING    0
#define CFG_PIECEVAL_NONE    0

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

