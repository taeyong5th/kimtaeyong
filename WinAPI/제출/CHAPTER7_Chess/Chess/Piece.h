#pragma once
#include <Windows.h>
#include <list>
#include <atlstr.h>
#include "GameDefine.h"
class Board;

class Piece
{
protected:
	LPCWSTR m_strBitmapName; // 피스의 모양
	BOARD_POSITION_X m_ix; // 피스의 위치 x
	BOARD_POSITION_Y m_iy; // 피스의 위치 y
	unsigned int m_imoveCount; // 피스를 움직인 횟수
	TEAM m_eTeam; // 백팀 or 흑팀
	bool m_bChoose; // 이 피스가 현재 선택(클릭)되었는지

public:
	virtual std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> getMovablePositions(Board* board) = 0; // piece가 이동할 수 있는 모든좌표 반환
	
	Piece* move(Board* board, BOARD_POSITION_X x, BOARD_POSITION_Y y); // board의 x, y 위치로 피스를 이동
	void drawMovablePositions(HDC hdc, int x, int y, Board *board); // piece가 이동 가능한 곳을 그린다.
	void draw(HDC hdc, int x, int y);
	std::pair<BOARD_POSITION_X, BOARD_POSITION_Y> getPosition();
	TEAM getTeam();
	Piece(LPCWSTR bitmapName, BOARD_POSITION_X x, BOARD_POSITION_Y y, TEAM team);
	virtual ~Piece();
};