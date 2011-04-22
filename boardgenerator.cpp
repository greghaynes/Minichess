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
	int x, y;
	Piece::Type piece;
	Player::Who player;
	for(itr = str, x = 0, y = 0;*itr;++itr,++x)
	{
		ch = tolower(*itr);
		switch(ch)
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
			case 'b':
				piece = Piece::Bishop;
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
				x=-1;
				++y;
				continue;
		}

		if(*itr == ch) // is lower
			player = Player::Player1;
		else
			player = Player::Player2;

		b->set(Location(x, y), BoardSlot(player, piece));
	}

	return b;
}

Board *BoardGenerator::matchStart(void)
{
	return BoardGenerator::fromString(
		"kqbnr\n"
		"ppppp\n"
		".....\n"
		".....\n"
		"PPPPP\n"
		"RNBQK\n");

}

