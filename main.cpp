#include "board.h"
#include "location.h"

int main(int argc, char **argv)
{
	Board b;
	b.get(Location(6, 0));

	return 0;
}

