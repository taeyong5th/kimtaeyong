#pragma once
#include "Piece.h"

class Queen : public Piece
{

public:
	
	std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> getMovablePositions(Board* board) override; // piece�� �̵��� �� �ִ� �����ǥ ��ȯ		
	std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> getAttackablePositions(Board* board) override; // piece�� ������ �� �ִ� �����ǥ ��ȯ
	Queen(LPCWSTR bitmapName, BOARD_POSITION_X x, BOARD_POSITION_Y y, TEAM team);
	~Queen();
};