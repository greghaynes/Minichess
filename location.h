#ifndef LOCATION_H
#define LOCATION_H

class Location
{

	public:
		Location(unsigned char x, unsigned char y);

		unsigned char x() const;
		unsigned char y() const;

	private:
		unsigned char m_x;
		unsigned char m_y;

};

#endif

