#pragma once
#include "Piece.h"

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8

class Board
{
private:
	Piece* _piecesOnMap[BOARD_WIDTH][BOARD_HEIGHT]; // 보드 위에 있는 피스
public:
	void setPiece(Piece* piece, int x, int y);  // x, y 위치에 piece를 놓음
	Piece* getPiece(int x, int y); // x, y 위치에 있는 piece를 반환
	Board();
	~Board();
};