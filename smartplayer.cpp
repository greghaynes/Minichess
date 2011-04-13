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
	negamax(b, who(), 3);
	return negamax_move;
}

int SmartPlayer::negamax(Board *b, Player::Who cur_player, int depth)
{
	Board tmp_board(*b);
	std::list<Move> *moves;
	std::list<Move>::iterator itr;

	if(depth == 0)
	{
		negamax_move = Move();
		return boardEval(b, cur_player);
	}
	depth--;

	moves = b->validMoves(cur_player);
	if(moves->size() == 0)
	{
		negamax_move = Move();
		return 0;
	}

	Move best_move = *(moves->begin());
	int max_score = CFG_GAMEVAL_LOSE;
	int tmp_score;
	Player::Who tmp_winner;
	for(itr = moves->begin();itr != moves->end();itr++)
	{
		tmp_board.move(*itr);

		tmp_winner = b->winner();
		if(tmp_winner != Player::None)
		{
			if(tmp_winner == cur_player)
				tmp_score = CFG_GAMEVAL_WIN;
			else
				tmp_score = CFG_GAMEVAL_LOSE;
		}
		else
			tmp_score = - negamax(&tmp_board, Player::opponent(cur_player), depth);

		if(tmp_score == CFG_GAMEVAL_WIN)
		{
			delete moves;
			negamax_move = *itr;
			return tmp_score;
		}

		if(tmp_score < max_score)
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
	return b->populationCount(cur_player) - b->populationCount(Player::opponent(cur_player));
}

