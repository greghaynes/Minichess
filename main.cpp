#include "boardgenerator.h"
#include "randomplayer.h"
#include "smartplayer.h"
#include "boardslot.h"
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
#if 0
	Board *b = new Board;
	b->set(Location(0, 0), BoardSlot(Player::Player2, Piece::Rook));
	std::cout << b->populationCount(Player::Player1) - b->populationCount(Player::Player2) << std::endl;
	std::string *str = b->toString();
	std::cout << *str;
	delete str;
	delete b;
	return 0;
#endif

	Game g(BoardGenerator::matchStart());
	g.setPlayer(new RandomPlayer(Player::Player1));
	g.setPlayer(new SmartPlayer(Player::Player2));
	g.play();

	printWinner(*g.board());

	return 0;
}

