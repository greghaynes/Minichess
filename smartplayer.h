#ifndef SMART_PLAYER_H
#define SMART_PLAYER_H

#include "player.h"
#include "config.h"
#include "transposetable.h"

#include <list>

class Move;

class SmartPlayer
	: public Player
{

	public:
		SmartPlayer(void);
		SmartPlayer(Player::Who);

		Move move(Board *b, struct timeval *time_remain, int move);

	private:
		float negamax(Board *b, Player::Who cur_player, int depth, const Move &move, float alpha, float beta);
		float boardEval(Board *b, Player::Who cur_player, std::list<Move> &moves);

#if USE_TTABLE
		TransposeTable m_tt;
#endif

};

#endif

