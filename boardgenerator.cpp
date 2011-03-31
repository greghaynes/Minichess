#include "boardgenerator.h"
#include "config.h"
#include "board.h"
#include "boardslot.h"

#include <ctype.h>

Board *BoardGenerator::fromString(const char *str)
{
	Board *b = new Board;

	const char *itr;
	char ch;
	int ndx;
	int x, y;
	Piece::Type piece;
	Player::Who player;
	for(itr = str, ndx = 0;*itr;++itr,++ndx)
	{
		ch = tolower(*itr);
		switch(*itr)
		{
			case 'p':
				piece = Piece::Pawn;
				break;
			case 'r':
				piece = Piece::Rook;
				break;
			case 'n':
				piece = Piece::Knight;
				break;
			case 'q':
				piece = Piece::Queen;
				break;
			case 'k':
				piece = Piece::King;
				break;
			case '.':
				continue;
			default:
				ndx--;
				continue;
		}

		if(*itr == ch) // is lower
			player = Player::Player1;
		else
			player = Player::Player2;

		x = ndx % CFG_BOARD_WIDTH;
		y = ndx / CFG_BOARD_HEIGHT;

		b->set(Location(x, y), BoardSlot(player, piece));
	}
}

