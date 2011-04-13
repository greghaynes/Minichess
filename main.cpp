#include "boardgenerator.h"
#include "randomplayer.h"
#include "smartplayer.h"
#include "game.h"

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
	Game g(BoardGenerator::matchStart());
	g.setPlayer(new RandomPlayer(Player::Player1));
	g.setPlayer(new SmartPlayer(Player::Player2));
	g.play();

	printWinner(*g.board());

	return 0;
}

