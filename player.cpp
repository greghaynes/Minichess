#include "player.h"

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

