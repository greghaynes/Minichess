#include "board.h"

#include <stdio.h>
#include <string.h>
#include <stdexcept>

Board::Board(void)
	: m_winner(Player::None)
{
}

Board::Board(const Board &other)
	: m_winner(other.winner())
{
	memcpy(m_board, other.get(Location(0, 0)), sizeof(BoardSlot)*CFG_BOARD_WIDTH*CFG_BOARD_HEIGHT);
}

Board::~Board(void)
{
}

const BoardSlot *Board::get(const Location &l) const
{
	if(!isValidLocation(l))
		return 0;
	return &m_board[l.x()][l.y()];
}

void Board::set(const Location &l, const BoardSlot &p)
{
	if(!isValidLocation(l))
		return;
	m_board[l.x()][l.y()] = p;
}

void Board::move(Move move)
{
	// Update winner if capturing king
	if(get(move.to())->piece() == Piece::King)
	{
		if(get(move.to())->owner() == Player::Player1)
			m_winner = Player::Player1;
		else
			m_winner = Player::Player2;
	}

	set(move.to(), *get(move.from()));
	set(move.from(), BoardSlot(Player::None, Piece::None));
}

std::list<Move> *Board::validMoves(Player::Who player) const
{
	std::list<Move> *ret = new std::list<Move>;
	std::list<Location> *pieces;
	std::list<Location>::const_iterator piece_itr;
	std::list<Move> *pieceMoves;
	std::list<Move>::iterator pieceMoves_itr;
	const BoardSlot *piece;

	// If there is a winner, no valid moves
	if(m_winner != Player::None)
		return ret;

	pieces = playerPieces(player);

	for(piece_itr = pieces->begin();piece_itr != pieces->end();++piece_itr)
	{
		piece = get(*piece_itr);
		pieceMoves = piece->validMoves(*this, *piece_itr);
		// Append moves for each piece to ret list
		for(pieceMoves_itr = pieceMoves->begin();pieceMoves_itr != pieceMoves->end();++pieceMoves_itr)
			ret->push_front(*pieceMoves_itr);
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
			if(get(Location(i, j))->owner() == player)
				ret->push_front(Location(i, j));
		}
	}

	return ret;
}

Player::Who Board::winner(void) const
{
	return m_winner;
}

std::string *Board::toString(void) const
{
	std::string *ret = new std::string;
	int i,j;
	for(i = 0;i < CFG_BOARD_HEIGHT;i++)
	{
		for(j = 0;j < CFG_BOARD_WIDTH;j++)
		{
			ret->push_back(get(Location(j, i))->toChar());
		}
		ret->push_back('\n');
	}
	return ret;
}

int Board::populationCount(Player::Who player) const
{
	int score = 0;
	int i, j;
	for(i=0;i<CFG_BOARD_WIDTH;++i)
	{
		for(j=0;j<CFG_BOARD_HEIGHT;++j)
		{
			if(m_board[i][j].owner() == player)
				score += m_board[i][j].value();
		}
	}
	return score;
}

bool Board::isValidLocation(const Location &l) const
{
	return l.x() >= 0 && l.y() >= 0
	       && l.x() < CFG_BOARD_WIDTH
	       && l.y() < CFG_BOARD_HEIGHT;
}

