#include "transposetable.h"

TransposeTable::TransposeTable(void)
{
}

TransposeTable::~TransposeTable()
{
}

void TransposeTable::getUsableEntry(const Board &b,
                                    unsigned char depth,
                                    float alpha,
                                    float beta,
                                    BoardTTEntry **entry)
{
	BoardTTEntry *t_entry;
	getEntry(b, &t_entry);
	*entry = 0;
	if(!t_entry)
		return;

	if(t_entry->depth < depth)
		return;

	if(t_entry->negamax < alpha || t_entry->negamax > beta)
		return;
	
	*entry = t_entry;
}

void TransposeTable::getEntry(const Board &b,
                              BoardTTEntry **entry)
{
	BoardTTEntry *t_entry = m_table.get(b.zobristKey());
	if(!t_entry) {
		*entry = 0;
		return;
	}
	if(t_entry->zobrist_key != b.zobristKey()) {
		*entry = 0;
		return;
	}
	*entry = t_entry;
}

void TransposeTable::insert(const Board &b, float negamax,
                            float alpha, float beta, unsigned char depth)
{
	BoardTTEntry *entry = m_table.get(b.zobristKey());

	entry->zobrist_key = b.zobristKey();
	entry->alpha = alpha;
	entry->beta = beta;
	entry->negamax = negamax;
	entry->depth = depth;
}

