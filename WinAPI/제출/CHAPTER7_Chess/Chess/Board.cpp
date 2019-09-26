#include "Board.h"

void Board::setPiece(Piece* piece, int x, int y)
{
	m_PiecesonBoard[x][y] = piece;
}

Piece* Board::getPiece(int x, int y)
{
	return m_PiecesonBoard[x][y];
}

Board::Board()
{
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		memset(m_PiecesonBoard[i], 0, sizeof(Piece*) * BOARD_HEIGHT);
	}
}

Board::~Board()
{
}
