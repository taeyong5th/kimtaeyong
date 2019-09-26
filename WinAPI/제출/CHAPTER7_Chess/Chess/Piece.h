#pragma once
#include <vector>
#include "GameDefine.h"
class Board;

class Piece
{
protected:
	int m_iBitmapID; // �ǽ��� ���
	int m_ix, m_iy; // �ǽ��� ��ġ
	unsigned int m_imoveCount; // �ǽ��� ������ Ƚ��
	TEAM m_eTeam; 

public:
	virtual bool move(Board* board, int x, int y) = 0; // board�� x, y ��ġ�� �ǽ��� �̵�
	virtual std::vector<std::pair<int, int>> getMovablePositions() = 0; // piece�� �̵��� �� �ִ� �����ǥ ��ȯ
	Piece(int bitmapId);
	~Piece();
};