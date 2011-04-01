#include "board.h"

#include <stdio.h>
#include <string.h>
#include <stdexcept>

Board::Board(void)
{
}

Board::Board(const Board &other)
{
	memcpy(m_board, &other.get(Location(0, 0)), sizeof(BoardSlot)*CFG_BOARD_WIDTH*CFG_BOARD_HEIGHT);
}

Board::~Board(void)
{
}

const BoardSlot &Board::get(const Location &l) const
{
#if CFG_BOARD_SAFE
	if(isValidLocation(l))
	{
		char errmsg[50];
		sprintf(errmsg, "Invalid location (%u, %u)", l.x(), l.y());
		throw std::invalid_argument(errmsg);
	}
#endif
	return m_board[l.x()][l.y()];
}

void Board::set(const Location &l, const BoardSlot &p)
{
#if CFG_BOARD_SAFE
	if(isValidLocation(l))
	{
		char errmsg[50];
		sprintf(errmsg, "Invalid location (%u, %u)", l.x(), l.y());
		throw std::invalid_argument(errmsg);
	}
#endif
	m_board[l.x()][l.y()] = p;
}

void Board::move(const Location &src, const Location &dest)
{
	set(dest, get(src));
	set(src, BoardSlot(Player::None, Piece::None));
}

std::list<Board*> *Board::validMoves(Player::Who player) const
{
	std::list<Location> *pieces = playerPieces(player);
	std::list<Location>::const_iterator piece_itr;
	std::list<Board*> *ret = new std::list<Board*>;
	std::list<Board*> *pieceMoves;
	std::list<Board*>::iterator pieceMoves_itr;
	const BoardSlot *piece;

	for(piece_itr = pieces->begin();piece_itr != pieces->end();++piece_itr)
	{
		piece = &get(*piece_itr);
		pieceMoves = piece->validMoves(*this, *piece_itr);
		delete pieceMoves;
	}
	delete pieces;

	return ret;
}

std::list<Location> *Board::playerPieces(Player::Who player) const
{
	std::list<Location> *ret = new std::list<Location>();
	int i, j;
	for(i = 0;i<CFG_BOARD_WIDTH;i++)
	{
		for(j = 0;j<CFG_BOARD_HEIGHT;j++)
		{
			if(get(Location(i, j)).owner() == player)
				ret->push_front(Location(i, j));
		}
	}

	return ret;
}

bool Board::isValidLocation(const Location &l) const
{
	return l.x() >= CFG_BOARD_WIDTH || l.y() >= CFG_BOARD_HEIGHT;
}

