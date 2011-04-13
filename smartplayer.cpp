#include "smartplayer.h"
#include "board.h"
#include "move.h"

#include <list>

static Move negamax_move;

SmartPlayer::SmartPlayer(void)
	: Player()
{
}

SmartPlayer::SmartPlayer(Player::Who who)
	: Player(who)
{
}

Move SmartPlayer::move(Board *b)
{
}

int SmartPlayer::negamax(Board *b, Player::Who cur_player)
{
	Board tmp_board(*b);
	std::list<Move> *moves = b->validMoves(who());
	std::list<Move>::iterator itr;

	if(moves->size() == 0)
	{
		negamax_move = Move();
		return 0;
	}

	Move best_move;
	int max_score;
	int tmp_score;
	for(itr = moves->begin();itr != moves->end();itr++)
	{
		tmp_board.move(*itr);

		tmp_score = negamax(&tmp_board, Player::opponent(cur_player));
		if(tmp_score > max_score)
		{
			best_move = *itr;
			max_score = tmp_score;
		}

		tmp_board.move((*itr).getInverted());
	}

	negamax_move = best_move;
	return max_score;
	
	delete moves;
}

int SmartPlayer::boardEval(Board *b, Player::Who cur_player)
{
	return b->populationCount(cur_player);
}

