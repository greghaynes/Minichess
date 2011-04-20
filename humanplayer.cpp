#include "humanplayer.h"
#include "board.h"
#include "move.h"

#include <list>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

static bool has_srand;

HumanPlayer::HumanPlayer(void)
	: Player()
{
	init();
}

HumanPlayer::HumanPlayer(Player::Who who)
	: Player(who)
{
	init();
}

Move HumanPlayer::move(Board *b, struct timeval *time_remain)
{
	Move mv;
	std::list<Move> validMoves;
	std::list<Move>::iterator moves_itr;
	bool has_move = false;
	char input[11];
	int cols[2];
	int rows[2]; 

	while(!has_move)
	{
		std::cout << "Enter move: ";
		std::cin.getline(input, 10);
		rows[0] = input[0] - 'A';
		rows[1] = input[3] - 'A';
		cols[0] = input[1] - '1';
		cols[1] = input[4] - '1';
		mv = Move(Location(rows[0], cols[0]), Location(rows[1], cols[1]));

		b->validMoves(who(), validMoves);
		for(moves_itr = validMoves.begin();moves_itr != validMoves.end();++moves_itr)
		{
			if(mv == *moves_itr)
				return mv;
		}

		std::cout << "Invalid move (" << (int)mv.from().x() << " " << (int)mv.from().y() << "-" << (int)mv.to().x() << " " << (int)mv.to().y() << ")\n";
	}
}

void HumanPlayer::init(void)
{
	if(!has_srand)
	{
		timeval tv;
		gettimeofday(&tv, 0);

		srand(tv.tv_usec);
		has_srand = true;	
	}
}

