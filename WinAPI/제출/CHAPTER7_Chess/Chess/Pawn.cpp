#include "Pawn.h"
#include "Board.h"

std::vector<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> Pawn::getMovablePositions(Board* board)
{
	std::vector<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> vec;
	int direction = 1; // �Ʒ� ���� = 1, �� ���� = -1
	// ��� ���� ���������θ� ������ �� �ִ�.
	if (m_eTeam == TEAM_WHITE) 
		direction = -1;

	// ������ Ƚ���� 0�̸� ������ �ִ� 2ĭ �̵� ����
	if (m_imoveCount == 0)
	{
		vec.push_back(std::make_pair(m_ix, BOARD_POSITION_Y(m_iy + direction)));
		vec.push_back(std::make_pair(m_ix, BOARD_POSITION_Y(m_iy + direction + direction)));
	}
	else
	{
		vec.push_back(std::make_pair(m_ix, BOARD_POSITION_Y(m_iy + direction)));
	}

	// ���� �⹰�� ���� ������ �̵� �Ұ�


	return vec;
}

Pawn::Pawn(LPCWSTR bitmapName, BOARD_POSITION_X x, BOARD_POSITION_Y y, TEAM team) :
	Piece(bitmapName, x, y, team)
{

}

Pawn::~Pawn()
{
}
