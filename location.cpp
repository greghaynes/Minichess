#include "location.h"

Location::Location(unsigned char x, unsigned char y)
	: m_x(x)
	, m_y(y)
{
}

unsigned char Location::x() const
{
	return m_x;
}

unsigned char Location::y() const
{
	return m_y;
}

