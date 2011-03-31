#ifndef BOARD_H
#define BOARD_H

#include "config.h"
#include "boardslot.h"
#include "location.h"

#include <vector>

class Board
{

	public:
		Board(void);
		Board(const Board &other);

		const BoardSlot &get(const Location &l) const;
		void set(const Location &l, const BoardSlot &p);

		void move(const Location &src, const Location &dest);

		const BoardSlot *board(void) const;

		std::vector<Board*> *validMoves(Player::Who player) const;

		const std::vector<Location> *playerPieces(Player::Who player) const;

	private:
		bool isValidLocation(const Location &l) const;
		int locationToNdx(const Location &l) const;

		BoardSlot m_board[CFG_BOARD_WIDTH*CFG_BOARD_HEIGHT];

};

#endif

