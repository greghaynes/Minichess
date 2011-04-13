#ifndef SMART_PLAYER_H
#define SMART_PLAYER_H

#include "player.h"

class SmartPlayer
	: public Player
{

	public:
		SmartPlayer(void);
		SmartPlayer(Player::Who);

		Move move(Board *b);

	private:
		int negamax(Board *b, Player::Who cur_player);
		int boardEval(Board *b, Player::Who cur_player);

};

#endif

