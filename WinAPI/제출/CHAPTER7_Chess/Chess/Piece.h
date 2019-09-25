#pragma once
#include <vector>
class Board;

class Piece
{
private:
	int m_iBitmapID; // �ǽ��� ���
	unsigned int m_imoveCount; // �ǽ��� ������ Ƚ��

public:
	virtual bool move(Board* board, int x, int y) = 0; // board�� x, y ��ġ�� �ǽ��� �̵�
	virtual std::vector<std::pair<int, int>> getMovablePositions() = 0; // piece�� �̵��� �� �ִ� �����ǥ ��ȯ
	Piece(int bitmapId);
	~Piece();
};