#include "board.h"
#include "zobrist.h"

#include <stdio.h>
#include <string.h>
#include <stdexcept>

Board::Board(void)
	: m_winner(Player::None)
	, m_pop_count(0)
	, m_zobrist_key(0)
{
	pawn_dists[0] = 0;
	pawn_dists[1] = 1;
	int i, j;
	for(i = 0;i<CFG_BOARD_WIDTH;++i)
	{
		for(j=0;j<CFG_BOARD_HEIGHT;++j)
			Zobrist::key(m_board[i][j], Location(j, i), m_zobrist_key);
	}
}

Board::Board(const Board &other)
	: m_winner(other.winner())
	, m_pop_count(other.populationCount(Player::Player1))
	, m_zobrist_key(other.zobristKey())
{
	pawn_dists[0] = other.pawnDist(Player::Player1);
	pawn_dists[1] = other.pawnDist(Player::Player2);
	memcpy(m_board, other.get(Location(0, 0)), sizeof(BoardSlot)*CFG_BOARD_WIDTH*CFG_BOARD_HEIGHT);
}

Board::~Board(void)
{
}

bool Board::operator==(const Board &other) const
{
	int i, j;
	for(i=0;i<CFG_BOARD_WIDTH;i++) {
		for(j=0;j<CFG_BOARD_HEIGHT;j++) {
			if(m_board[i][j] != *other.get(Location(i, j)))
				return false;
		}
	}
	return true;
}

bool Board::operator!=(const Board &other) const
{
	return !(*this == other);
}

const BoardSlot *Board::get(const Location &l) const
{
	if(!isValidLocation(l))
		return 0;
	return &m_board[l.x()][l.y()];
}

void Board::set(const Location &l, const BoardSlot &p)
{

	// Update key
	Zobrist::key(*get(l), l, m_zobrist_key);
	Zobrist::key(p, l, m_zobrist_key);

	if(!isValidLocation(l))
		return;
	m_board[l.x()][l.y()] = p;
}

void Board::move(Move move)
{
	Player::Who victim = get(move.to())->owner();
	if(victim == Player::Player1)
		m_pop_count -= get(move.to())->value();
	else if(victim == Player::Player2)
		m_pop_count += get(move.to())->value();

	if(get(move.to())->piece() == Piece::King)
	{
		// Update winner if capturing king
		m_winner = get(move.from())->owner();
	}
	else if(get(move.from())->piece() == Piece::Pawn)
	{
		if(move.to().y() == 5 || move.to().y() == 0)
		{
			if(get(move.from())->owner() == Player::Player1)
				m_pop_count += CFG_PIECEVAL_QUEEN - 1;
			else
				m_pop_count -= CFG_PIECEVAL_QUEEN - 1;
			set(move.to(), BoardSlot(get(move.from())->owner(), Piece::Queen));
			set(move.from(), BoardSlot(Player::None, Piece::None));
			return;
		}
	}

	set(move.to(), *get(move.from()));
	set(move.from(), BoardSlot(Player::None, Piece::None));
}

void Board::validMoves(Player::Who player, std::list<Move> &moves) const
{
	std::list<Move> *ret = &moves;
	std::list<Location> pieces;
	std::list<Location>::const_iterator piece_itr;
	std::list<Move> pieceMoves;
	std::list<Move>::iterator pieceMoves_itr;
	const BoardSlot *piece;

	// If there is a winner, no valid moves
	if(m_winner != Player::None)
		return;

	playerPieces(player, pieces);

	for(piece_itr = pieces.begin();piece_itr != pieces.end();++piece_itr)
	{
		piece = get(*piece_itr);
		piece->validMoves(*this, *piece_itr, pieceMoves);
		// Append moves for each piece to ret list
		for(pieceMoves_itr = pieceMoves.begin();pieceMoves_itr != pieceMoves.end();++pieceMoves_itr)
			ret->push_front(*pieceMoves_itr);
		pieceMoves.clear();
	}

	return;
}

void Board::playerPieces(Player::Who player, std::list<Location> &location) const
{
	std::list<Location> *ret = &location;
	int i, j;
	for(i = 0;i<CFG_BOARD_WIDTH;i++)
	{
		for(j = 0;j<CFG_BOARD_HEIGHT;j++)
		{
			if(get(Location(i, j))->owner() == player)
				ret->push_front(Location(i, j));
		}
	}
}

Player::Who Board::winner(void) const
{
	return m_winner;
}

void Board::setWinner(Player::Who who)
{
	m_winner = who;
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
	if(player == Player::Player2)
		return -m_pop_count;
	return m_pop_count;
}

void Board::setPopulationCount(int value)
{
	m_pop_count = value;
}

uint64_t Board::zobristKey(void) const
{
	return m_zobrist_key;
}

int Board::pawnDist(Player::Who player) const
{
	return pawn_dists[player-1];
}

bool Board::isValidLocation(const Location &l) const
{
	return l.x() >= 0 && l.y() >= 0
	       && l.x() < CFG_BOARD_WIDTH
	       && l.y() < CFG_BOARD_HEIGHT;
}

