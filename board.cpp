#include "board.h"

#include <stdio.h>
#include <string.h>
#include <stdexcept>

BoardSlot::BoardSlot(Player::Who owner, Piece::Type piece)
	: m_piece(piece)
	, m_owner(owner)
{
}

Board::Board(void)
{
}

Board::Board(const Board &other)
{
	memcpy(m_board, other.board(), sizeof(BoardSlot)*CFG_BOARD_WIDTH*CFG_BOARD_HEIGHT);
}

const BoardSlot &Board::get(const Location &l) const
{
#if CFG_BOARD_SAFE
	if(l.x() >= CFG_BOARD_WIDTH || l.y() >= CFG_BOARD_HEIGHT)
	{
		char errmsg[50];
		sprintf(errmsg, "Invalid location (%u, %u)", l.x(), l.y());
		throw std::invalid_argument(errmsg);
	}
#endif
	return m_board[locationToNdx(l)];
}

void Board::set(const Location &l, const BoardSlot &p)
{
#if CFG_BOARD_SAFE
	if(l.x() >= CFG_BOARD_WIDTH || l.y() >= CFG_BOARD_HEIGHT)
	{
		char errmsg[50];
		sprintf(errmsg, "Invalid location (%u, %u)", l.x(), l.y());
		throw std::invalid_argument(errmsg);
	}
#endif
	m_board[locationToNdx(l)] = p;
}

void Board::move(const Location &src, const Location &dest)
{
	set(dest, get(src));
	set(src, BoardSlot(Player::None, Piece::None));
}

const BoardSlot *Board::board(void) const
{
	return m_board;
}

int Board::locationToNdx(const Location &l) const
{
	return l.x() + (l.y() * CFG_BOARD_WIDTH);
}

