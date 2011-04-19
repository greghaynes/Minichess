#include "game.h"

#include <iostream>
#include <string>
#include <stdexcept>

Game::Game(void)
	: m_board(0)
	, m_isPlaying(false)
{
	m_players[0] = 0;
	m_players[1] = 0;

	timerclear(&m_expiredTime[0]);
	timerclear(&m_expiredTime[1]);
}

Game::Game(Board *b)
	: m_isPlaying(false)
{
	m_board = b;
	m_players[0] = 0;
	m_players[1] = 0;

	timerclear(&m_expiredTime[0]);
	timerclear(&m_expiredTime[1]);
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
	bool valid_move;
	struct timeval tv_start, tv_end, tv_elapsed;
	while(isPlaying() && m_board->winner() == Player::None && i < 40)
	{
		gettimeofday(&tv_start, 0);
		valid_move = movePlayer(Player::Player1);
		gettimeofday(&tv_end, 0);
		timersub(&tv_end, &tv_start, &tv_elapsed);
		timeradd(&m_expiredTime[ndxFromPlayer(Player::Player1)], &tv_elapsed, &m_expiredTime[ndxFromPlayer(Player::Player1)]);
		printTimeLeft();
		if(!valid_move)
			break;

		gettimeofday(&tv_start, 0);
		valid_move = movePlayer(Player::Player2);
		gettimeofday(&tv_end, 0);
		timersub(&tv_end, &tv_start, &tv_elapsed);
		timeradd(&m_expiredTime[ndxFromPlayer(Player::Player2)], &tv_elapsed, &m_expiredTime[ndxFromPlayer(Player::Player2)]);
		printTimeLeft();
		if(!valid_move)
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
	switch(who)
	{
		case Player::Player1:
			return 0;
		case Player::Player2:
			return 1;
		default:
			throw std::runtime_error("Invalid player in playerToNdx");
	}
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

void Game::printTimeLeft(void) const
{
	struct timeval rem, total;
	total.tv_sec = 360;
	total.tv_usec = 0;

	timersub(&total, &m_expiredTime[ndxFromPlayer(Player::Player1)], &rem);
	std::cout << rem.tv_sec / 60  << ":" << rem.tv_sec % 60 << " - ";
	timersub(&total, &m_expiredTime[ndxFromPlayer(Player::Player2)], &rem);
	std::cout << rem.tv_sec / 60 << ":" << rem.tv_sec % 60 << std::endl;
	std::cout << std::endl;
}

