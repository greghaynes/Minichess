#ifndef PLAYER_H
#define PLAYER_H

#include "move.h"

#include <sys/time.h>

class Board;

class Player
{

	public:
		enum Who
		{
			None,
			Player1,
			Player2
		};

		static Player::Who opponent(Player::Who);

		Player(void);
		Player(Player::Who);

		Player::Who who(void) const;

		virtual Move move(Board *board, struct timeval *time_remain, int move) = 0;

	private:
		Player::Who m_who;

};

#endif

