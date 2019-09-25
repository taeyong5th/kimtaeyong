#pragma once
#include <vector>
class Board;

class Piece
{
private:
	int m_iBitmapID; // 피스의 모양
	unsigned int m_imoveCount; // 피스를 움직인 횟수

public:
	virtual bool move(Board* board, int x, int y) = 0; // board의 x, y 위치로 피스를 이동
	virtual std::vector<std::pair<int, int>> getMovablePositions() = 0; // piece가 이동할 수 있는 모든좌표 반환
	Piece(int bitmapId);
	~Piece();
};