#include "King.h"
#include "Board.h"

std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> King::getMovablePositions(Board* board)
{
	std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> posList;
	Piece* p;
	const int move_x[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
	const int move_y[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };

	// 8���� ��ġ�� �̵� ����
	for (int i = 0; i < 8; i++)
	{
		p = board->getPiece(BOARD_POSITION_X(m_ix + move_x[i]), BOARD_POSITION_Y(m_iy + move_y[i]));
		// p�� ��ġ�� ����ְų� ���� ������ �̵� ������ ��
		if (p == nullptr || m_eTeam != p->getTeam())
		{
			posList.push_back(std::make_pair(BOARD_POSITION_X(m_ix + move_x[i]), BOARD_POSITION_Y(m_iy + move_y[i])));
		}
	}

	// ü���� ���� �̵��� �� ���� ��ǥ�� ����
	for (auto iter = posList.begin(); iter != posList.end(); )
	{
		if (iter->first < POS_A || iter->first > POS_H || iter->second < POS_8 || iter->second > POS_1)
		{
			iter = posList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	
	BOARD_POSITION_X origin_x = m_ix;
	BOARD_POSITION_Y origin_y = m_iy;
	
	// ŷ�� ����(üũ) ���ϴ� ��ġ ����
	for (auto iter = posList.begin(); iter != posList.end(); )
	{
		// ŷ�� �ӽ÷� �̵� ��Ų��.
		p = this->move(board, iter->first, iter->second);

		// ���� ���ݰ����� ��� ��ǥ�� ���Ѵ�.
		std::set<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> attackedPosList = board->getAttackablePositions((TEAM)((m_eTeam + 1) % TEAM_COUNT));
		
		// ŷ�� ��ġ�� ���� �ڸ��� �ǵ�����.
		this->move(board, origin_x, origin_y);
		board->setPiece(p, iter->first, iter->second);		

		// ���� ���� ���� �޴� �����̸� �����Ѵ�.
		auto atkPos = attackedPosList.find(*iter);
		if (atkPos != attackedPosList.end())
		{
			iter = posList.erase(iter);
		}
		else
		{
			++iter;
		}		
	}
	return posList;
}

std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> King::getAttackablePositions(Board* board)
{
	std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> posList;
	Piece* p;
	const int move_x[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
	const int move_y[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };

	// 8���� ��ġ�� �̵� ����
	for (int i = 0; i < 8; i++)
	{
		p = board->getPiece(BOARD_POSITION_X(m_ix + move_x[i]), BOARD_POSITION_Y(m_iy + move_y[i]));
		// p�� ��ġ�� ����ְų� ���� ������ �̵� ������ ��
		if (p == nullptr || m_eTeam != p->getTeam())
		{
			posList.push_back(std::make_pair(BOARD_POSITION_X(m_ix + move_x[i]), BOARD_POSITION_Y(m_iy + move_y[i])));
		}
	}

	// ü���� ���� �̵��� �� ���� ��ǥ�� ����
	for (auto iter = posList.begin(); iter != posList.end(); )
	{
		if (iter->first < POS_A || iter->first > POS_H || iter->second < POS_8 || iter->second > POS_1)
		{
			iter = posList.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	return posList;
}

King::King(LPCWSTR bitmapName, BOARD_POSITION_X x, BOARD_POSITION_Y y, TEAM team) :
	Piece(bitmapName, x, y, team)
{

}

King::~King()
{
}
