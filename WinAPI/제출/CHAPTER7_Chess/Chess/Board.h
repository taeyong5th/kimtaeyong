#pragma once
#include <Windows.h>
#include <set>
#include "GameDefine.h"
#include "Piece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "BitmapManager.h"

class Board
{
private:
	int m_ix, m_iy; // ���尡 �׷��� �»� ��ġ
	Piece* m_PiecesonBoard[BOARD_WIDTH][BOARD_HEIGHT]; // ���� ���� �ִ� �ǽ�
public:
	void setPiece(Piece* piece, BOARD_POSITION_X x, BOARD_POSITION_Y y);  // x, y ��ġ�� piece�� ����
	Piece* getPiece(BOARD_POSITION_X x, BOARD_POSITION_Y y); // x, y ��ġ�� �ִ� piece�� ��ȯ
	Piece* getPiece(POINT point); // point ��ǥ�� �ִ� �ǽ��� ��ȯ
	void draw(HDC hdc, int x = 0, int y = 0); // x, y ��ġ�� ���带 �׸���.
	std::pair<BOARD_POSITION_X, BOARD_POSITION_Y> calcPosition(POINT point); // Ŭ���� ��ǥ�� �ش��ϴ� ���� ��ǥ�� ��ȯ�Ѵ�.
	bool isChecked(TEAM team);  // team�� ŷ�� üũ�� ��������
	Board();
	~Board();
};