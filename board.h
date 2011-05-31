#ifndef BOARD_H
#define BOARD_H

#include "config.h"
#include "player.h"
#include "location.h"
#include "boardslot.h"
#include "move.h"

#include <list>
#include <string>

#include <stdint.h>

class Board
{

	public:
		Board(void);
		Board(const Board &other);
		~Board(void);

		bool operator==(const Board &other) const;
		bool operator!=(const Board &other) const;

		const BoardSlot *get(const Location &l) const;
		void set(const Location &l, const BoardSlot &p);

		void move(Move move);

		void validMoves(Player::Who player, std::list<Move> &moves) const;

		void playerPieces(Player::Who player, std::list<Location> &location) const;

		Player::Who winner(void) const;
		void setWinner(Player::Who who);

		std::string *toString(void) const;

		int populationCount(Player::Who player) const;

		void setPopulationCount(int value);

		uint64_t zobristKey(void) const;

		int pawnDist(Player::Who player) const;

	private:
		bool isValidLocation(const Location &l) const;

		BoardSlot m_board[CFG_BOARD_WIDTH][CFG_BOARD_HEIGHT];
		Player::Who m_winner;
		char m_pop_count;
		unsigned char pawn_dists[2];
		uint64_t m_zobrist_key;

};

#endif

