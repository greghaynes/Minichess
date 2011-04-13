#include "move.h"

Move::Move(void)
{
}

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

bool Move::isValid(void) const
{
	return m_from != m_to;
}

Move Move::getInverted(void) const
{
	return Move(m_to, m_from);
}

