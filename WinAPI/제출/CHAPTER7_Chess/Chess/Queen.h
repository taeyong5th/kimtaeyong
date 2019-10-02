#pragma once
#include "Piece.h"

class Queen : public Piece
{

public:
	
	std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> getMovablePositions(Board* board) override; // piece가 이동할 수 있는 모든좌표 반환		
	std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> getAttackablePositions(Board* board) override; // piece가 공격할 수 있는 모든좌표 반환
	Queen(LPCWSTR bitmapName, BOARD_POSITION_X x, BOARD_POSITION_Y y, TEAM team);
	~Queen();
};