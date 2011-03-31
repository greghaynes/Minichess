#include "board.h"
#include "location.h"

int main(int argc, char **argv)
{
	Board b;
	b.get(Location(0, 0));

	return 0;
}

