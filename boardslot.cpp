#include "boardslot.h"
#include "board.h"

BoardSlot::BoardSlot(Player::Who owner, Piece::Type piece)
{
	m_piece = (char)piece;
	m_owner = (char)owner;
}

Piece::Type BoardSlot::piece(void) const
{
	return (Piece::Type)m_piece;
}

Player::Who BoardSlot::owner(void) const
{
	return (Player::Who)m_owner;
}

std::list<Move> *BoardSlot::validMoves(const Board &b, const Location &loc) const
{
	std::list<Move> *moves = new std::list<Move>;
	
	switch(m_piece)
	{
		case Piece::Pawn:
			if(m_owner == Player::Player1)
			{
				scanMoves(moves, b, loc, 0, 1, false, 1);
				// check for captures
			}
			else
			{
				scanMoves(moves, b, loc, 0, -1, false, 1);
				// check for captures
			}
			break;
		case Piece::Knight:
			scanMoves(moves, b, loc, 1, 2, true, 1);
			scanMoves(moves, b, loc, 1, -2, true, 1);
			scanMoves(moves, b, loc, -1, 2, true, 1);
			scanMoves(moves, b, loc, -1, -2, true, 1);
			break;
		case Piece::Bishop:
			// Diags
			scanMoves(moves, b, loc, 1, 1);
			scanMoves(moves, b, loc, 1, -1);
			scanMoves(moves, b, loc, -1, 1);
			scanMoves(moves, b, loc, -1, -1);

			// Color change
			scanMoves(moves, b, loc, 1, 0, false, 1);
			scanMoves(moves, b, loc, -1, 0, false, 1);
			scanMoves(moves, b, loc, 0, 1, false, 1);
			scanMoves(moves, b, loc, 0, -1, false, 1);
			break;
		case Piece::Rook:
			// Laterals
			scanMoves(moves, b, loc, 1, 0);
			scanMoves(moves, b, loc, -1, 0);
			scanMoves(moves, b, loc, 0, 1);
			scanMoves(moves, b, loc, 0, -1);
			break;
		case Piece::Queen:
			// Diags
			scanMoves(moves, b, loc, 1, 1);
			scanMoves(moves, b, loc, 1, -1);
			scanMoves(moves, b, loc, -1, 1);
			scanMoves(moves, b, loc, -1, -1);
			
			// Laterals
			scanMoves(moves, b, loc, 1, 0);
			scanMoves(moves, b, loc, -1, 0);
			scanMoves(moves, b, loc, 0, 1);
			scanMoves(moves, b, loc, 0, -1);
			break;
		case Piece::King:
			scanMoves(moves, b, loc, 1, 0, true, 1);
			scanMoves(moves, b, loc, -1, 0, true, 1);
			scanMoves(moves, b, loc, 0, 1, true, 1);
			scanMoves(moves, b, loc, 0, -1, true, 1);
			break;
	}

	return moves;
}

void BoardSlot::scanMoves(std::list<Move> *vals,
                          const Board &b,
                          const Location &origin,
                          int dx,
                          int dy,
                          bool can_capture,
                          int max_cnt) const
{
	scanMoves(vals,
	          b,
	          origin,
	          Location(origin.x() + dx, origin.y() + dy),
	          dx,
	          dy,
	          0,
	          can_capture,
	          max_cnt);
}

void BoardSlot::scanMoves(std::list<Move> *vals,
                      const Board &b,
                      const Location &origin,
                      const Location &l,
                      int dx,
                      int dy,
                      int cnt,
                      bool can_capture,
                      int max_cnt) const
{
	const BoardSlot *piece = b.get(l);
	if(!piece)
		return;
	if(piece->owner() == m_owner)
		return;
	if(piece->owner() == Player::None || can_capture)
	{
		vals->push_front(Move(origin, l));
		if(piece->owner() == Player::None)
		{
			++cnt;
			if(!max_cnt || max_cnt > cnt)
				scanMoves(vals,
				          b,
				          origin,
				          Location(l.x()+dx, l.y()+dy),
				          dx,
				          dy,
				          cnt,
				          can_capture,
				          max_cnt);
		}
	}
}

