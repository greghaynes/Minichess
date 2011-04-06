#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "board.h"

class Game
{

	public:
		Game(void);
		Game(const Board &b);
		~Game(void);

		const Board *board(void) const;

		const Player *player(Player::Who) const;

		/* Takes ownership of player */
		void setPlayer(Player *player);

		bool play(void);
		bool stop(void);

		bool isPlaying(void);

	private:
		int ndxFromPlayer(Player::Who who) const;

		Board *m_board;
		Player *m_players[2];
		bool m_isPlaying;

};

#endif

