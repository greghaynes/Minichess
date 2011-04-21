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

Move SmartPlayer::move(Board *b, struct timeval *time_remain)
{
	int i;
	int alpha, beta;
	for(i=1;i<7;i+=2)
	{
		alpha = -CFG_INFINITY;
		beta = CFG_INFINITY;
		if(negamax(b, who(), i, Move(), alpha, beta) == CFG_GAMEVAL_WIN)
			return negamax_move;
	}
	return negamax_move;
}

int SmartPlayer::negamax(Board *b, Player::Who cur_player, int depth, const Move &move, int alpha, int beta)
{
	Board *tmp_board;
	std::list<Move> moves;
	std::list<Move>::iterator itr;

	// Check for end state
	if(b->winner() != Player::None) {
		if(b->winner() == cur_player) {
			negamax_move = move;
			alpha = CFG_GAMEVAL_WIN;
			return alpha;
		} else {
			negamax_move = move;
			alpha = CFG_GAMEVAL_LOSE;
			return alpha;
		}
	}

	// Check for max depth
	if(depth == 0) {
		negamax_move = Move();
		alpha = boardEval(b, cur_player);
		return alpha;
	}
	depth--;

	// Load moves
	b->validMoves(cur_player, moves);

	// No movew -> Draw
	if(moves.size() == 0) {
		negamax_move = Move();
		alpha = CFG_GAMEVAL_LOSE;
		return alpha;
	}

	Move best_move = *(moves.begin());
	int max_score = CFG_GAMEVAL_LOSE;
	int tmp_score;
	for(itr = moves.begin();itr != moves.end();itr++) {
		tmp_board = new Board(*b);
		tmp_board->move(*itr);

		tmp_score = - negamax(tmp_board, Player::opponent(cur_player), depth, *itr, -beta, -alpha);

		if(tmp_score > max_score) {
			best_move = *itr;
			max_score = tmp_score;
		}

		delete tmp_board;

		if(max_score >= beta)
			break;
	}

	negamax_move = best_move;
	alpha = max_score;
	return alpha;
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

