#ifndef BOARD_H
#define BOARD_H

#include "config.h"
#include "location.h"

namespace Player
{
	enum Who
	{
		None,
		Player1,
		Player2
	};
}

namespace Piece
{
	enum Type
	{
		None,
		Pawn,
		Rook,
		Knight,
		Bishop,
		Queen,
		King
	};
}

class BoardSlot
{
	public:
		BoardSlot(Player::Who owner=Player::None, Piece::Type piece=Piece::None);

	private:
		char m_piece;
		char m_owner;
};


class Board
{

	public:
		Board(void);
		Board(const Board &other);

		BoardSlot &get(const Location &l) const;
		void set(const Location &l, const BoardSlot &p);

		const BoardSlot *board(void) const;

	private:
		BoardSlot m_board[CFG_BOARD_WIDTH*CFG_BOARD_HEIGHT];

};

#endif

