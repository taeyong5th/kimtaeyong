#pragma once
#include "Piece.h"

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8

class Board
{
private:
	Piece* _piecesOnMap[BOARD_WIDTH][BOARD_HEIGHT]; // ���� ���� �ִ� �ǽ�
public:
	void setPiece(Piece* piece, int x, int y);  // x, y ��ġ�� piece�� ����
	Piece* getPiece(int x, int y); // x, y ��ġ�� �ִ� piece�� ��ȯ
	Board();
	~Board();
};