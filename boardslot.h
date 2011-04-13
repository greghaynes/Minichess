#ifndef BOARDSLOT_H
#define BOARDSLOT_H

#include "config.h"
#include "player.h"
#include "location.h"
#include "move.h"

#include <list>

class Board;

class BoardSlot
{

	public:
		BoardSlot(Player::Who owner=Player::None, Piece::Type piece=Piece::None);

		Piece::Type piece(void) const;
		Player::Who owner(void) const;

		std::list<Move> *validMoves(const Board &b, const Location &loc) const;

		char toChar(void) const;

		int value(void) const;

	private:
		void scanMoves(std::list<Move> *vals,
								  const Board &b,
								  const Location &origin,
								  int dx,
								  int dy,
								  bool can_capture=true,
								  int max_cnt=0) const;

		void scanMoves(std::list<Move> *vals,
							  const Board &b,
							  const Location &origin,
							  const Location &l,
							  int dx,
							  int dy,
							  int cnt,
							  bool can_capture=true,
							  int max_cnt=0) const;

		char m_state;

};

#endif

