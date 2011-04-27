#include "boardslot.h"
#include "board.h"

BoardSlot::BoardSlot(char ch)
	: m_state(ch)
{
}

BoardSlot::BoardSlot(Player::Who owner, Piece::Type piece)
{
	m_state = (char)piece;
	m_state |= (char)(owner<<4);
}

Piece::Type BoardSlot::piece(void) const
{
	return (Piece::Type)(m_state & 0xF);
}

Player::Who BoardSlot::owner(void) const
{
	return (Player::Who)((m_state & 0xF0) >> 4);
}

void BoardSlot::validMoves(const Board &b, const Location &loc, std::list<Move> &moves) const
{
	Location t_loc;
	const BoardSlot *t_slot;
	
	switch(piece())
	{
		case Piece::Pawn:
			if(owner() == Player::Player1)
			{
				scanMoves(&moves, b, loc, 0, 1, false, 1);

				t_loc = Location(loc.x()+1,loc.y()+1);
				t_slot = b.get(t_loc);
				if(t_slot && t_slot->owner() == Player::Player2)
					moves.push_front(Move(loc, t_loc));

				t_loc = Location(loc.x()-1,loc.y()+1);
				t_slot = b.get(t_loc);
				if(t_slot && t_slot->owner() == Player::Player2)
					moves.push_front(Move(loc, t_loc));
			}
			else
			{
				scanMoves(&moves, b, loc, 0, -1, false, 1);

				t_loc = Location(loc.x()+1,loc.y()-1);
				t_slot = b.get(t_loc);
				if(t_slot && t_slot->owner() == Player::Player1)
					moves.push_front(Move(loc, t_loc));

				t_loc = Location(loc.x()-1,loc.y()-1);
				t_slot = b.get(t_loc);
				if(t_slot && t_slot->owner() == Player::Player1)
					moves.push_front(Move(loc, t_loc));
			}
			break;
		case Piece::Knight:
			scanMoves(&moves, b, loc, 1, 2, true, 1);
			scanMoves(&moves, b, loc, 1, -2, true, 1);
			scanMoves(&moves, b, loc, -1, 2, true, 1);
			scanMoves(&moves, b, loc, -1, -2, true, 1);

			scanMoves(&moves, b, loc, 2, 1, true, 1);
			scanMoves(&moves, b, loc, 2, -1, true, 1);
			scanMoves(&moves, b, loc, -2, 1, true, 1);
			scanMoves(&moves, b, loc, -2, -1, true, 1);
			break;
		case Piece::Bishop:
			// Diags
			scanMoves(&moves, b, loc, 1, 1);
			scanMoves(&moves, b, loc, 1, -1);
			scanMoves(&moves, b, loc, -1, 1);
			scanMoves(&moves, b, loc, -1, -1);

			// Color change
			scanMoves(&moves, b, loc, 1, 0, false, 1);
			scanMoves(&moves, b, loc, -1, 0, false, 1);
			scanMoves(&moves, b, loc, 0, 1, false, 1);
			scanMoves(&moves, b, loc, 0, -1, false, 1);
			break;
		case Piece::Rook:
			// Laterals
			scanMoves(&moves, b, loc, 1, 0);
			scanMoves(&moves, b, loc, -1, 0);
			scanMoves(&moves, b, loc, 0, 1);
			scanMoves(&moves, b, loc, 0, -1);
			break;
		case Piece::Queen:
			// Diags
			scanMoves(&moves, b, loc, 1, 1);
			scanMoves(&moves, b, loc, 1, -1);
			scanMoves(&moves, b, loc, -1, 1);
			scanMoves(&moves, b, loc, -1, -1);
			
			// Laterals
			scanMoves(&moves, b, loc, 1, 0);
			scanMoves(&moves, b, loc, -1, 0);
			scanMoves(&moves, b, loc, 0, 1);
			scanMoves(&moves, b, loc, 0, -1);
			break;
		case Piece::King:
			scanMoves(&moves, b, loc, 1, 0, true, 1);
			scanMoves(&moves, b, loc, -1, 0, true, 1);
			scanMoves(&moves, b, loc, 0, 1, true, 1);
			scanMoves(&moves, b, loc, 0, -1, true, 1);

			scanMoves(&moves, b, loc, 1, 1, true, 1);
			scanMoves(&moves, b, loc, -1, -1, true, 1);
			scanMoves(&moves, b, loc, 1, -1, true, 1);
			scanMoves(&moves, b, loc, -1, 1, true, 1);
			break;
	}
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

char BoardSlot::toChar(void) const
{
	char ch;
	switch(piece())
	{
		case Piece::None:
			ch = '.';
			break;
		case Piece::Pawn:
			ch = 'P';
			break;
		case Piece::Rook:
			ch = 'R';
			break;
		case Piece::Bishop:
			ch = 'B';
			break;
		case Piece::Knight:
			ch = 'N';
			break;
		case Piece::King:
			ch = 'K';
			break;
		case Piece::Queen:
			ch = 'Q';
			break;
		default:
			ch = '.';
	}
	if(owner() == Player::Player1)
		ch = tolower(ch);

	return ch;
}

float BoardSlot::value(void) const
{
	switch(piece())
	{
		case Piece::Pawn:
			return CFG_PIECEVAL_PAWN;
		case Piece::Rook:
			return CFG_PIECEVAL_ROOK;
		case Piece::Bishop:
			return CFG_PIECEVAL_BISHOP;
		case Piece::Knight:
			return CFG_PIECEVAL_KNIGHT;
		case Piece::King:
			return CFG_PIECEVAL_KING;
		case Piece::Queen:
			return CFG_PIECEVAL_QUEEN;
		case Piece::None:
		default:
			return CFG_PIECEVAL_NONE;
	}
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
	if(piece->owner() == owner())
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

