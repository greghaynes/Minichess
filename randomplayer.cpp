#include "randomplayer.h"
#include "board.h"
#include "move.h"

#include <list>

#include <stdlib.h>
#include <sys/time.h>

static bool has_srand;

RandomPlayer::RandomPlayer(void)
	: Player()
{
	init();
}

RandomPlayer::RandomPlayer(Player::Who who)
	: Player(who)
{
	init();
}

Move RandomPlayer::move(Board *b)
{
	std::list<Move> *moves = b->validMoves(who());
	if(!moves->size())
		return Move();
	int randval = rand() % moves->size();
	std::list<Move>::iterator itr;
	int i;
	for(itr=moves->begin(),i=0;itr != moves->end();++i,++itr)
	{
		if(i==randval)
			return *itr;
	}
	return Move();
}

void RandomPlayer::init(void)
{
	if(!has_srand)
	{
		timeval tv;
		gettimeofday(&tv, 0);

		srand(tv.tv_usec);
		has_srand = true;	
	}
}

