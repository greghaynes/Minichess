#ifndef BOARD_H
#define BOARD_H

#include "config.h"
#include "location.h"
#include "boardslot.h"

#include <list>

class Board
{

	public:
		Board(void);
		Board(const Board &other);
		~Board(void);

		const BoardSlot *get(const Location &l) const;
		void set(const Location &l, const BoardSlot &p);

		void move(const Location &src, const Location &dest);

		std::list<Board*> *validMoves(Player::Who player) const;

		std::list<Location> *playerPieces(Player::Who player) const;

	private:
		bool isValidLocation(const Location &l) const;

		BoardSlot m_board[CFG_BOARD_WIDTH][CFG_BOARD_HEIGHT];

};

#endif

