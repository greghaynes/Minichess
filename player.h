#ifndef PLAYER_H
#define PLAYER_H

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

		Player(void);
		Player(Player::Who);

		Player::Who who(void) const;

		virtual Board *move(Board *board) = 0;

	private:
		Player::Who m_who;

};

#endif

