#ifndef IMCS_GAME_H
#define IMCS_GAME_H

#include "player.h"

#include <stdio.h>

class ImcsGame
{

	public:
		ImcsGame(void);
		~ImcsGame(void);

		void setPlayer(Player *p);

		void play(const char *username, const char *pass, char piece = '?');

	private:
		void startPlaying(void);

		Player *m_player;
		int m_sock_fd;
		FILE *m_sock_ffd;
		bool m_valid_conn;

};

#endif

