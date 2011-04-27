#include "smartplayer.h"
#include "board.h"
#include "move.h"

#include <iostream>
#include <algorithm>
#include <numeric>

#include <sys/time.h>

static Move negamax_move;
static bool has_srand;

SmartPlayer::SmartPlayer(void)
	: Player()
{
}

SmartPlayer::SmartPlayer(Player::Who who)
	: Player(who)
{
}

Move SmartPlayer::move(Board *b, struct timeval *time_remain)
{
	int i;
	float alpha, beta;
	for(i=1;i<7;i+=2)
	{
		alpha = -CFG_INFINITY;
		beta = CFG_INFINITY;
		if(negamax(b, who(), i, Move(), alpha, beta) == CFG_GAMEVAL_WIN)
			return negamax_move;
	}
	return negamax_move;
}

float SmartPlayer::negamax(Board *b, Player::Who cur_player, int depth, const Move &move, float alpha, float beta)
{
	Board *tmp_board;
	std::list<Move> moves;
	std::list<Move>::iterator itr;

	// Check for end state
	if(b->winner() != Player::None) {
		if(b->winner() == cur_player) {
			negamax_move = move;
			return CFG_GAMEVAL_WIN;
		} else {
			negamax_move = move;
			return CFG_GAMEVAL_LOSE;
		}
	}

	// Check for max depth
	if(depth == 0) {
		negamax_move = Move();
		return boardEval(b, cur_player, moves);
	}
	depth--;

	// Load moves
	b->validMoves(cur_player, moves);

	// No movew -> Draw
	if(moves.size() == 0) {
		std::cout << "No moves!\n";
		negamax_move = Move();
		return CFG_GAMEVAL_LOSE;
	}

	// Shuffle moves
	// Not worth it
	//shuffleMoves(moves);

	Move best_move = *(moves.begin());
	float max_score = CFG_GAMEVAL_LOSE;
	float tmp_score;

	int prev_pop_count;
	BoardSlot prev_from, prev_to;
	Player::Who prev_win;
	for(itr = moves.begin();itr != moves.end();itr++) {
		prev_from = *b->get(itr->from());
		prev_to = *b->get(itr->to());
		prev_pop_count = b->populationCount(Player::Player1);
		prev_win = b->winner();
		b->move(*itr);

		tmp_score = - negamax(b, Player::opponent(cur_player), depth, *itr, -beta, -alpha);

		if(tmp_score > max_score) {
			best_move = *itr;
			max_score = tmp_score;
		}

		b->set(itr->from(), prev_from);
		b->set(itr->to(), prev_to);
		b->setPopulationCount(prev_pop_count);
		b->setWinner(prev_win);

		if(max_score >= beta)
			break;
	}

	negamax_move = best_move;
	return max_score;
}

float SmartPlayer::boardEval(Board *b, Player::Who cur_player, std::list<Move> &moves)
{
	Player::Who tmp_winner;
	float score;
	tmp_winner = b->winner();
	if(tmp_winner != Player::None)
	{
		if(tmp_winner == cur_player)
			score = CFG_GAMEVAL_WIN;
		else
			score = CFG_GAMEVAL_LOSE;
	}
	else
	{
		score = b->populationCount(cur_player) - b->populationCount(Player::opponent(cur_player));
		score += moves.size() / 100;
	}

	return score;
}

