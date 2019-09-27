#pragma once
#include "Piece.h"

class Pawn : public Piece
{

public:
	
	std::vector<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> getMovablePositions(Board* board) override; // piece가 이동할 수 있는 모든좌표 반환	
	Pawn(LPCWSTR bitmapName, BOARD_POSITION_X x, BOARD_POSITION_Y y, TEAM team);
	~Pawn();
};