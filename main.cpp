#include "board.h"
#include "boardslot.h"
#include "config.h"
#include "location.h"

#include <iostream>

void printBoardSlot(const BoardSlot &bs)
{
	switch(bs.piece())
	{
		case Piece::None:
			std::cout << ".";
			break;
		case Piece::Pawn:
			std::cout << "P";
			break;
		case Piece::Rook:
			std::cout << "R";
			break;
		case Piece::Bishop:
			std::cout << "B";
			break;
		case Piece::Knight:
			std::cout << "K";
			break;
		case Piece::King:
			std::cout << "!";
			break;
		case Piece::Queen:
			std::cout << "Q";
	}
	std::cout << " ";
}

void printBoard(const Board &b)
{
	int i,j;
	for(i = 0;i < CFG_BOARD_HEIGHT;i++)
	{
		for(j = 0;j < CFG_BOARD_WIDTH;j++)
		{
			printBoardSlot(b.get(Location(j, i)));
		}
		std::cout << "\n";
	}
}

int main(int argc, char **argv)
{
	Board b;
	b.set(Location(0, 0), BoardSlot(Player::Player1, Piece::Queen));
	printBoard(b);

	return 0;
}

