#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "player.h"

class HumanPlayer
	: public Player
{

	public:
		HumanPlayer(void);
		HumanPlayer(Player::Who who);

		Move move(Board *b, struct timeval *time_remain);

	private:
		void init(void);

};

#endif

