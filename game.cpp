#include "game.h"

#include <iostream>
#include <string>

Game::Game(void)
	: m_board(0)
	, m_isPlaying(false)
{
	m_players[0] = 0;
	m_players[1] = 0;
}

Game::Game(Board *b)
	: m_isPlaying(false)
{
	m_board = b;
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

bool Game::play(void)
{
	if(!m_board)
		return false;

	if(isPlaying())
		return false;

	m_isPlaying = true;
	int i = 0;
	Move mv;
	while(isPlaying() && m_board->winner() == Player::None && i < 40)
	{
		if(!movePlayer(Player::Player1))
			break;
		if(!movePlayer(Player::Player2))
			break;
		i++;
	}
	m_isPlaying = false;
	return true;
}

bool Game::stop(void)
{
	if(!isPlaying())
		return false;
	m_isPlaying = false;
	return true;
}

bool Game::isPlaying(void) const
{
	return m_isPlaying;
}

int Game::ndxFromPlayer(Player::Who who) const
{
	return who - Player::Player1;
}

bool Game::movePlayer(Player::Who who)
{
	std::string *str;
	Move mv;

	mv = m_players[ndxFromPlayer(who)]->move(m_board);
	if(!mv.isValid())
		return false;

	m_board->move(mv);

	str = m_board->toString();
	std::cout << *str << "\n";
	delete str;

	return true;
}

