#include "boardgenerator.h"
#include "humanplayer.h"
#include "randomplayer.h"
#include "smartplayer.h"
#include "boardslot.h"
#include "imcsgame.h"

#include <iostream>

#include <ctype.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

void printWinner(const Board &b)
{
	if(b.winner() == Player::Player1)
		std::cout << "Player 1 ";
	else if(b.winner() == Player::Player2)
		std::cout << "Player 2 ";
	else
		std::cout << "No one ";
	std::cout << "wins!\n";
}

int main(int argc, char **argv)
{
	ImcsGame g;
	g.setPlayer(new SmartPlayer(Player::Player2));
	g.play("sasquatch", "p@ssw0rd", '?');

	return 0;
}

