#include "smartplayer.h"
#include "board.h"
#include "move.h"

#include <list>
#include <iostream>

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
	negamax(b, who(), 5, Move());
	return negamax_move;
}

int SmartPlayer::negamax(Board *b, Player::Who cur_player, int depth, const Move &move)
{
	Board *tmp_board;
	std::list<Move> *moves;
	std::list<Move>::iterator itr;

	if(b->winner() != Player::None)
	{
		if(b->winner() == cur_player)
		{
			negamax_move = move;
			return CFG_GAMEVAL_WIN;
		}
		else
		{
			negamax_move = move;
			return CFG_GAMEVAL_LOSE;
		}
	}

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
	for(itr = moves->begin();itr != moves->end();itr++)
	{
		tmp_board = new Board(*b);
		tmp_board->move(*itr);

		tmp_score = - negamax(tmp_board, Player::opponent(cur_player), depth, *itr);

		if(tmp_score > max_score)
		{
			best_move = *itr;
			max_score = tmp_score;
		}

		delete tmp_board;
	}

	negamax_move = best_move;
	return max_score;
	
	delete moves;
	delete tmp_board;
}

int SmartPlayer::boardEval(Board *b, Player::Who cur_player)
{
	Player::Who tmp_winner;
	int score;
	tmp_winner = b->winner();
	if(tmp_winner != Player::None)
	{
		if(tmp_winner == cur_player)
			score = CFG_GAMEVAL_WIN;
		else
			score = CFG_GAMEVAL_LOSE;
	}
	else
		score = b->populationCount(cur_player) - b->populationCount(Player::opponent(cur_player));

	return score;
}

