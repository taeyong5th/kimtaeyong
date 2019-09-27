#pragma once
#include <Windows.h>
#include "GameDefine.h"
#include "Piece.h"
#include "Pawn.h"
#include "BitmapManager.h"

class Board
{
private:
	int m_ix, m_iy; // 보드가 그려질 좌상 위치
	Piece* m_PiecesonBoard[BOARD_WIDTH][BOARD_HEIGHT]; // 보드 위에 있는 피스
public:
	void setPiece(Piece* piece, BOARD_POSITION_X x, BOARD_POSITION_Y y);  // x, y 위치에 piece를 놓음
	Piece* getPiece(BOARD_POSITION_X x, BOARD_POSITION_Y y); // x, y 위치에 있는 piece를 반환
	Piece* getPiece(POINT point); // point 좌표에 있는 피스를 반환
	void draw(HDC hdc, int x = 0, int y = 0); // x, y 위치에 보드를 그린다.
	std::pair<BOARD_POSITION_X, BOARD_POSITION_Y> calcPosition(POINT point);
	Board();
	~Board();
};