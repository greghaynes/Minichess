#include "board.h"
#include "boardslot.h"
#include "config.h"
#include "location.h"
#include "boardgenerator.h"

#include <iostream>

#include <ctype.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

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

void printWinner(Board &b)
{
	if(b.winner() == Player::Player1)
		std::cout << "Player 1 ";
	else if(b.winner() == Player::Player2)
		std::cout << "Player 2 ";
	else
		std::cout << "No one ";
	std::cout << "wins!\n";
}

void makeRandomMove(Board *&b, Player::Who player)
{
	std::list<Board*> *moves = b->validMoves(player);
	std::list<Board*>::iterator itr;
	Board *move_board;
	int move, i;

	if(moves->size() == 0)
	{
#if PRINT_MOVES
		printWinner(*b);
#endif
		delete moves;
		delete b;
		b = 0;
		return;
	}

	// Not correct distribution but should be good enough
	move = rand() % moves->size();


	delete b;
        for(i=0,itr = moves->begin();itr != moves->end();++itr,++i)
        {
		if(i == move)
			b = *itr;
		else
			delete *itr;
	}
	delete moves;
}

int main(int argc, char **argv)
{
	struct timeval tv;

	if(-1 == gettimeofday(&tv, 0))
	{
		perror("Getting current time.");
		return 1;
	}

	srand(tv.tv_usec);
	
	int game_cnt;
	for(game_cnt=0;game_cnt<NUM_GAMES;++game_cnt)
	{
		Board *b = BoardGenerator::matchStart();

#if PRINT_MOVES
		printBoard(*b);
		std::cout << "\n";
#endif
		int i;
		for(i = 0;i < 40 && b;++i)
		{
			makeRandomMove(b, Player::Player1);
			if(!b)
				break;
#if PRINT_MOVES
			std::cout << "P1:\n";
			printBoard(*b);
			std::cout << "\n";
#endif
			makeRandomMove(b, Player::Player2);
			if(b)
			{
#if PRINT_MOVES
				std::cout << "P2:\n";
				printBoard(*b);
				std::cout << "\n";
#endif
			}
		}
		if(b)
		{
			delete b;
#if PRINT_MOVES
			std::cout << "Draw! (max moves limit)\n";
#endif
		}
	}

	return 0;
}

