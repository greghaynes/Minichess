#include "board.h"
#include "boardslot.h"
#include "config.h"
#include "location.h"
#include "boardgenerator.h"

#include <iostream>

#include <ctype.h>

void printBoardSlot(const BoardSlot &bs)
{
	char ch;
	switch(bs.piece())
	{
		case Piece::None:
			ch = '.';
			break;
		case Piece::Pawn:
			ch = 'P';
			break;
		case Piece::Rook:
			ch = 'R';
			break;
		case Piece::Bishop:
			ch = 'B';
			break;
		case Piece::Knight:
			ch = 'N';
			break;
		case Piece::King:
			ch = 'K';
			break;
		case Piece::Queen:
			ch = 'Q';
			break;
		default:
			ch = '.';
	}
	if(bs.owner() == Player::Player1)
		ch = tolower(ch);
	std::cout << ch;
}

void printBoard(const Board &b)
{
	int i,j;
	for(i = 0;i < CFG_BOARD_HEIGHT;i++)
	{
		for(j = 0;j < CFG_BOARD_WIDTH;j++)
		{
			printBoardSlot(*b.get(Location(j, i)));
		}
		std::cout << "\n";
	}
}

void printMoves(Board &b)
{
	std::list<Board*> *moves = b.validMoves(Player::Player1);
	std::list<Board*>::iterator itr;

	for(itr = moves->begin();itr != moves->end();++itr)
	{
		printBoard(**itr);
		std::cout << "\n";
		delete *itr;
	}
	delete moves;
}

int main(int argc, char **argv)
{
	Board *b = BoardGenerator::matchStart();

	std::list<Board*> *moves = b->validMoves(Player::Player1);
	std::list<Board*>::iterator itr;

	for(itr = moves->begin();itr != moves->end();++itr)
	{
		printMoves(**itr);
		std::cout << "\n---------------------\n\n";
		delete *itr;
	}
	delete moves;

	delete b;

	return 0;
}

