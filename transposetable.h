#ifndef TRANSPOSE_TABLE_H
#define TRANSPOSE_TABLE_H

#include "hashtable.h"
#include "board.h"

#include <list>

struct BoardTTEntry
{
	uint64_t zobrist_key;
	float alpha;
	float beta;
	float negamax;
};

class TransposeTable
{

	public:
		TransposeTable(void);
		~TransposeTable(void);

		void getEntry(const Board &b,
		              const BoardTTEntry **entry);

		void insert(const Board &b, float negamax,
		            float alpha, float beta);

	private:
		Hashtable<BoardTTEntry> m_table;
		std::list<BoardTTEntry*> m_entries;

};

#endif

