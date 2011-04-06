#ifndef LOCATION_H
#define LOCATION_H

class Location
{

	public:
		Location(void);
		Location(unsigned char x, unsigned char y);

		unsigned char x(void) const;
		unsigned char y(void) const;

		bool operator==(const Location &other) const;
		bool operator!=(const Location &other) const;

	private:
		unsigned char m_loc;

};

#endif

