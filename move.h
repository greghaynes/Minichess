#ifndef MOVE_H
#define MOVE_H

#include "location.h"

class Move
{

	public:
		Move(Location from, Location to);

		Location from(void) const;
		Location to(void) const;


	private:
		Location m_from;
		Location m_to;

};

#endif

