#ifndef LOCATION_H
#define LOCATION_H

class Location
{

	public:
		Location(unsigned char x, unsigned char y);

		signed char x() const;
		signed char y() const;

	private:
		signed char m_x;
		signed char m_y;

};

#endif

