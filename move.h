#ifndef MOVE_H
#define MOVE_H

#include "location.h"

class Move
{

	public:
		Move(void);
		Move(Location from, Location to);

		bool operator==(const Move &other) const;
		bool operator!=(const Move &other) const;

		Location from(void) const;
		Location to(void) const;

		bool isValid(void) const;

		Move getInverted(void) const;

	private:
		Location m_from;
		Location m_to;

};

#endif

