#ifndef SMART_PLAYER_H
#define SMART_PLAYER_H

#include "player.h"

#include <list>

class Move;

class SmartPlayer
	: public Player
{

	public:
		SmartPlayer(void);
		SmartPlayer(Player::Who);

		Move move(Board *b, struct timeval *time_remain);

	private:
		float negamax(Board *b, Player::Who cur_player, int depth, const Move &move, float alpha, float beta);
		float boardEval(Board *b, Player::Who cur_player, std::list<Move> &moves);
		void shuffleMoves(std::list<Move> &moves) const;

};

#endif

