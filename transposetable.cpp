#include "transposetable.h"

TransposeTable::TransposeTable(void)
{
}

TransposeTable::~TransposeTable()
{
}

void TransposeTable::getEntry(const Board &b,
                              const BoardTTEntry **entry)
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
                            float alpha, float beta)
{
	BoardTTEntry *entry = new BoardTTEntry;

	entry->zobrist_key = b.zobristKey();
	entry->alpha = alpha;
	entry->beta = beta;
	entry->negamax = negamax;

	m_entries.push_front(entry);
	m_table.set(b.zobristKey(), entry);
}

