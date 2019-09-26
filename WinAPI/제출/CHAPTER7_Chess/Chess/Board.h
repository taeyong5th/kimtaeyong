#pragma once
#include "GameDefine.h"
#include "Piece.h"

class Board
{
private:
	Piece* m_PiecesonBoard[BOARD_WIDTH][BOARD_HEIGHT]; // ���� ���� �ִ� �ǽ�
public:
	void setPiece(Piece* piece, int x, int y);  // x, y ��ġ�� piece�� ����
	Piece* getPiece(int x, int y); // x, y ��ġ�� �ִ� piece�� ��ȯ
	Board();
	~Board();
};