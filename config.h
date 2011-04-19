#ifndef CONFIG_H
#define CONFIG_H

#define CFG_BOARD_WIDTH      5
#define CFG_BOARD_HEIGHT     6

#define PRINT_MOVES          1

#define NUM_GAMES            1

#define CFG_PIECEVAL_PAWN    1
#define CFG_PIECEVAL_ROOK    10
#define CFG_PIECEVAL_KNIGHT  7
#define CFG_PIECEVAL_BISHOP  7
#define CFG_PIECEVAL_QUEEN   15
#define CFG_PIECEVAL_KING    0 
#define CFG_PIECEVAL_NONE    0
#define CFG_GAMEVAL_WIN      1000
#define CFG_GAMEVAL_LOSE     -1000

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

