#ifndef TRANSPOSE_TABLE_H
#define TRANSPOSE_TABLE_H

#include "hashtable.h"
#include "board.h"

#include <list>

struct BoardTTEntry
{
	uint64_t zobrist_key;
	unsigned char depth;
	float alpha;
	float beta;
	float negamax;
};

class TransposeTable
{

	public:
		TransposeTable(void);
		~TransposeTable(void);

		void getUsableEntry(const Board &b,
		                    unsigned char needed_depth,
		                    float cur_alpha,
		                    float cur_beta,
		                    BoardTTEntry **entry);
					

		void getEntry(const Board &b,
		              BoardTTEntry **entry);

		void insert(const Board &b, float negamax,
		            float alpha, float beta, unsigned char depth);

	private:
		Hashtable<BoardTTEntry> m_table;
		std::list<BoardTTEntry*> m_entries;

};

#endif

