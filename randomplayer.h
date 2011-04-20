#ifndef RANDOM_PLAYER_H
#define RANDOM_PLAYER_H

#include "player.h"

class RandomPlayer
	: public Player
{

	public:
		RandomPlayer(void);
		RandomPlayer(Player::Who who);

		Move move(Board *b, struct timeval *time_remain);

	private:
		void init(void);

};

#endif

