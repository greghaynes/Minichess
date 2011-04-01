#ifndef CONFIG_H
#define CONFIG_H

#define CFG_BOARD_WIDTH      5
#define CFG_BOARD_HEIGHT     6

namespace Player
{
	enum Who
	{
		None,
		Player1,
		Player2
	};
}

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

