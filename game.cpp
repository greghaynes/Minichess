#include "game.h"

Game::Game(void)
	: m_board(0)
{
	m_players[0] = 0;
	m_players[1] = 0;
}

Game::Game(const Board &b)
{
	m_board = new Board(b);
	m_players[0] = 0;
	m_players[1] = 0;
}

Game::~Game(void)
{
	if(m_board)
		delete m_board;
	if(m_players[0])
		delete m_players[0];
	if(m_players[1])
		delete m_players[1];
}

const Board *Game::board(void) const
{
	return m_board;
}

const Player *Game::player(Player::Who who) const
{
	return m_players[ndxFromPlayer(who)];
}

void Game::setPlayer(Player *player)
{
	int ndx = ndxFromPlayer(player->who());
	if(m_players[ndx])
		delete m_players[ndx];
	m_players[ndx] = player;
}

int Game::ndxFromPlayer(Player::Who who) const
{
	return who - Player::Player1;
}

