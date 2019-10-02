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
	int m_ix, m_iy; // 보드가 그려질 좌상 위치
	Piece* m_PiecesonBoard[BOARD_WIDTH][BOARD_HEIGHT]; // 보드 위에 있는 피스
public:
	void setPiece(Piece* piece, BOARD_POSITION_X x, BOARD_POSITION_Y y);  // x, y 위치에 piece를 놓음	
	Piece* getPiece(BOARD_POSITION_X x, BOARD_POSITION_Y y); // x, y 위치에 있는 piece를 반환
	Piece* getPiece(POINT point); // point 좌표에 있는 피스를 반환
	void draw(HDC hdc, int x = 0, int y = 0); // x, y 위치에 보드를 그린다.
	void drawMovablePositions(HDC hdc, TEAM team); // team이 이동가능한 모든 위치를 그린다.
	std::pair<BOARD_POSITION_X, BOARD_POSITION_Y> calcPosition(POINT point); // 클릭한 좌표에 해당하는 보드 좌표를 반환한다.
	std::set<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> getAttackablePositions(TEAM team); // team이 공격가능한 모든 좌표를 반환한다.
	std::set<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> getMovablePositions(TEAM team); // team이 이동가능한 모든 좌표를 반환한다.
	bool isChecked(TEAM team);  // team의 킹이 체크당하는 상태인지
	void clear(); // 보드에 있는 모든 피스를 지운다.
	Board();
	~Board();
};