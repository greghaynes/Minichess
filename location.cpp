#include "location.h"

Location::Location(void)
	: m_loc(0)
{
}

Location::Location(unsigned char x, unsigned char y)
{
	m_loc = x;
	m_loc |= (y << 4);
}

unsigned char Location::x(void) const
{
	return m_loc & 0xF;
}

unsigned char Location::y(void) const
{
	return ((m_loc & 0xF0) >> 4);
}

