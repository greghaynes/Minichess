#include "move.h"

Move::Move(Location from, Location to)
{
	m_from = from;
	m_to = to;
}

Location Move::from(void) const
{
	return m_from;
}

Location Move::to(void) const
{
	return m_to;
}

