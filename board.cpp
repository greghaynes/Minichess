#include "board.h"

#include <stdio.h>
#include <string.h>
#include <stdexcept>

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
	if(isValidLocation(l))
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
	if(isValidLocation(l))
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

std::vector<Board*> *Board::validMoves(Player::Who player) const
{
	const std::vector<Location> *pieces = playerPieces(player);
	std::vector<Location>::const_iterator piece_itr;
	std::vector<Board*> *ret = new std::vector<Board*>();
	std::vector<Board*> *pieceMoves;
	std::vector<Board*>::iterator pieceMoves_itr;

	for(piece_itr = pieces->begin();piece_itr != pieces->end();++piece_itr)
	{
		pieceMoves = get(*piece_itr).validMoves(*this, *piece_itr);
		for(pieceMoves_itr = pieceMoves->begin();pieceMoves_itr != pieceMoves->end();++pieceMoves_itr)
		{
			ret->push_back(*pieceMoves_itr);
		}
		delete pieceMoves;
	}

	return ret;
}

const std::vector<Location> *Board::playerPieces(Player::Who player) const
{
	std::vector<Location> *ret = new std::vector<Location>();
	int i, j;
	for(i = 0;i<CFG_BOARD_WIDTH;i++)
	{
		for(j = 0;j<CFG_BOARD_HEIGHT;j++)
		{
			if(get(Location(i, j)).owner() == player)
				ret->push_back(Location(i, j));
		}
	}

	return ret;
}

bool Board::isValidLocation(const Location &l) const
{
	return l.x() >= CFG_BOARD_WIDTH || l.y() >= CFG_BOARD_HEIGHT;
}

int Board::locationToNdx(const Location &l) const
{
	return l.x() + (l.y() * CFG_BOARD_WIDTH);
}

