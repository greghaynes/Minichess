#include "board.h"

#include <string.h>

Board::Board(void)
{
}

Board::Board(const Board &other)
{
	memcpy(m_board, other.board(), sizeof(BoardSlot)*CFG_BOARD_WIDTH*CFG_BOARD_HEIGHT);
}

const BoardSlot *Board::board(void) const
{
	return m_board;
}

