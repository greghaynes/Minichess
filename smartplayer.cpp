#include "smartplayer.h"
#include "board.h"
#include "move.h"

#include <iostream>
#include <algorithm>
#include <numeric>

#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

static Move negamax_move;
static bool has_srand;
static unsigned char cur_move_num;
static int alrm_secs;

static bool keep_searching;

void alarm_hdlr(int signal) {
	++alrm_secs;
	alarm(1);
}

SmartPlayer::SmartPlayer(void)
	: Player()
{
	signal(SIGALRM, alarm_hdlr);
	alarm(1);
	if(who() == Player::Player2)
		cur_move_num = 1;
}

SmartPlayer::SmartPlayer(Player::Who whoami)
	: Player(whoami)
{
	signal(SIGALRM, alarm_hdlr);
	alarm(1);
	if(who() == Player::Player2)
		cur_move_num = 1;
}

static unsigned char negamax_cur_depth;
static bool negamax_complete;
static int end_secs;

Move SmartPlayer::move(Board *b, struct timeval *time_remain, int move)
{
	int i;
	float alpha, beta;
	end_secs = alrm_secs + (time_remain->tv_sec / (80 - cur_move_num)) + 1;
	Move complete_mv;
	negamax_complete = true;
	for(i=1;i<100&&negamax_complete;i++)
	{
		alpha = -CFG_INFINITY;
		beta = CFG_INFINITY;
		negamax_complete = true;
		if(negamax(b, who(), i, Move(), alpha, beta) == CFG_GAMEVAL_WIN && negamax_complete) {
			cur_move_num += 2;
			return negamax_move;
		}
		if(negamax_complete)
			complete_mv = negamax_move;
	}

	cur_move_num += 2;
	return complete_mv;
}

float SmartPlayer::negamax(Board *b, Player::Who cur_player, int depth, const Move &move, float alpha, float beta)
{
	Board *tmp_board;
	std::list<Move> moves;
	std::list<Move>::iterator itr;
	float max_score = CFG_GAMEVAL_LOSE;

	negamax_cur_depth++;

	if(alrm_secs >= end_secs) {
		negamax_complete = false;
		return CFG_GAMEVAL_LOSE;
	}

	// Check for end state
	if(b->winner() != Player::None) {
		if(b->winner() == cur_player) {
			negamax_move = move;
			m_tt.insert(*b, CFG_GAMEVAL_WIN, alpha, beta, cur_move_num + negamax_cur_depth); 
			negamax_cur_depth--;
			return CFG_GAMEVAL_WIN;
		} else {
			negamax_move = move;
			m_tt.insert(*b, CFG_GAMEVAL_LOSE, alpha, beta, cur_move_num + negamax_cur_depth); 
			negamax_cur_depth--;
			return CFG_GAMEVAL_LOSE;
		}
	}

	// Check for TT hit
	BoardTTEntry *tt_entry;
	m_tt.getUsableEntry(*b, cur_move_num + negamax_cur_depth + depth, alpha, beta, &tt_entry);
	if(tt_entry) {
		negamax_cur_depth--;
		negamax_move = move;
		return tt_entry->negamax;
	}

	// Check for max depth
	if(depth == 0) {
		negamax_move = Move();
		max_score = boardEval(b, cur_player, moves);
		m_tt.insert(*b, max_score, alpha, beta, cur_move_num + negamax_cur_depth); 
		negamax_cur_depth--;
		return max_score;
	}
	depth--;

	// Load moves
	b->validMoves(cur_player, moves);

	// No movew -> Draw
	if(moves.size() == 0) {
		std::cout << "No moves!\n";
		m_tt.insert(*b, CFG_GAMEVAL_LOSE, alpha, beta, cur_move_num + negamax_cur_depth); 
		negamax_cur_depth--;
		negamax_move = Move();
		return CFG_GAMEVAL_LOSE;
	}

	// Shuffle moves
	// Not worth it
	//shuffleMoves(moves);

	Move best_move = *(moves.begin());
	float tmp_score;

	int prev_pop_count;
	BoardSlot prev_from, prev_to;
	Player::Who prev_win;
	for(itr = moves.begin();itr != moves.end();itr++) {
#if CFG_SLOW_CHECK
		tmp_board = new Board(*b);
#endif

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

#if CFG_SLOW_CHECK
		if(*tmp_board != *b) {
			std::cout << "do/undo failure!\n";
			exit(1);
		}
#endif

		if(max_score >= beta)
			break;
	}

	negamax_move = best_move;
	m_tt.insert(*b, max_score, alpha, beta, cur_move_num + negamax_cur_depth); 
	negamax_cur_depth--;
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

