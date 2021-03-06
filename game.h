#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "board.h"

#include <sys/time.h>

class Game
{

	public:
		Game(void);
		Game(Board *b);
		~Game(void);

		const Board *board(void) const;

		const Player *player(Player::Who) const;

		/* Takes ownership of player */
		void setPlayer(Player *player);

		bool play(void);
		bool stop(void);

		bool isPlaying(void) const;

	private:
		int ndxFromPlayer(Player::Who who) const;
		void printTimeLeft(void) const;
		void timeRemaining(Player::Who who, struct timeval *tv) const;
		bool movePlayer(Player::Who who, bool subtract_time = true);

		Board *m_board;
		Player *m_players[2];
		bool m_isPlaying;

		struct timeval m_expiredTime[2];

};

#endif

