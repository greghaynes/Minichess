#ifndef BOARDSLOT_H
#define BOARDSLOT_H

#include "config.h"
#include "location.h"

#include <list>

class Board;

class BoardSlot
{

	public:
		BoardSlot(Player::Who owner=Player::None, Piece::Type piece=Piece::None);

		Piece::Type piece(void) const;
		Player::Who owner(void) const;

		std::list<Board*> *validMoves(const Board &b, const Location &loc) const;

	private:
		void scanMoves(std::list<Board*> *vals,
								  const Board &b,
								  const Location &origin,
								  int dx,
								  int dy,
								  bool can_capture=true,
								  int max_cnt=0) const;

		void scanMoves(std::list<Board*> *vals,
							  const Board &b,
							  const Location &origin,
							  const Location &l,
							  int dx,
							  int dy,
							  int cnt,
							  bool can_capture=true,
							  int max_cnt=0) const;

		char m_piece;
		char m_owner;

};

#endif

