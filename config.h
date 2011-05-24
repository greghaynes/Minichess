#ifndef CONFIG_H
#define CONFIG_H

#define CFG_BOARD_WIDTH      5
#define CFG_BOARD_HEIGHT     6

#define PRINT_MOVES          1

#define NUM_GAMES            1

#define CFG_PIECEVAL_PAWN    1.0
#define CFG_PIECEVAL_ROOK    6.0
#define CFG_PIECEVAL_KNIGHT  4.0
#define CFG_PIECEVAL_BISHOP  5.0
#define CFG_PIECEVAL_QUEEN   13.0
#define CFG_PIECEVAL_KING    0.0
#define CFG_PIECEVAL_NONE    0.0
#define CFG_GAMEVAL_WIN      1000.0
#define CFG_GAMEVAL_LOSE     -1000.0

#define CFG_INFINITY         10000.0

#define CFG_SLOW_CHECK       0

#define CFG_T_TABLE_SIZE     (2 << 27)

namespace Piece
{
	enum Type
	{
		None = 0,
		Pawn = 1,
		Rook = 2,
		Knight = 3,
		Bishop = 4,
		Queen = 5,
		King = 6
	};
}

#endif

