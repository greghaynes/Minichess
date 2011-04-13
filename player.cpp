#include "player.h"

Player::Who Player::opponent(Player::Who who)
{
	switch(who)
	{
		case Player::Player1:
			return Player::Player2;
		case Player::Player2:
			return Player::Player1;
	}
	return Player::None;
}

Player::Player(void)
	: m_who(Player::None)
{
}

Player::Player(Player::Who who)
	: m_who(who)
{
}

Player::Who Player::who(void) const
{
	return m_who;
}

