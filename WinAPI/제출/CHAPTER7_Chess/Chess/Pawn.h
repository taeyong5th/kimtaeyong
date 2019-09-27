#pragma once
#include "Piece.h"

class Pawn : public Piece
{

public:
	
	std::vector<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> getMovablePositions(Board* board) override; // piece�� �̵��� �� �ִ� �����ǥ ��ȯ	
	Pawn(LPCWSTR bitmapName, BOARD_POSITION_X x, BOARD_POSITION_Y y, TEAM team);
	~Pawn();
};