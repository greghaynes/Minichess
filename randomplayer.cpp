#include "randomplayer.h"

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
		has_srand = true;	
	}
}

