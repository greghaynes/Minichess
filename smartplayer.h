#ifndef SMART_PLAYER_H
#define SMART_PLAYER_H

#include "player.h"

class Move;

class SmartPlayer
	: public Player
{

	public:
		SmartPlayer(void);
		SmartPlayer(Player::Who);

		Move move(Board *b, struct timeval *time_remain);

	private:
		int negamax(Board *b, Player::Who cur_player, int depth, const Move &move, int alpha, int beta);
		int boardEval(Board *b, Player::Who cur_player);

};

#endif

