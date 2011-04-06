#include "randomplayer.h"

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

Board *RandomPlayer::move(void)
{
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

