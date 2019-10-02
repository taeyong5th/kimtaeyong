#include "Queen.h"
#include "Board.h"

std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> Queen::getMovablePositions(Board* board)
{
	std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> posList;
	Piece* p;
	const int move_x[8] = { 0, 1, 0, -1, -1, 1, 1, -1};
	const int move_y[8] = { -1, 0, 1, 0, -1, -1, 1, 1};

	// �����¿�, �밢������ �̵�����
	for (int i = 0; i < 8; i++)
	{
		for (int x = move_x[i], y = move_y[i]; !((m_ix + x) < POS_A || (m_ix + x) > POS_H || (m_iy + y) < POS_8 || (m_iy + y) > POS_1); x += move_x[i], y += move_y[i])
		{
			p = board->getPiece(BOARD_POSITION_X(m_ix + x), BOARD_POSITION_Y(m_iy + y));
			// �̵��Ϸ��� ��ġ�� ����ְų� ���� ������ �̵� ����
			if (p == nullptr || m_eTeam != p->getTeam())
			{
				posList.push_back(std::make_pair(BOARD_POSITION_X(m_ix + x), BOARD_POSITION_Y(m_iy + y)));
			}

			// �̵��Ϸ��� ��ġ�� �⹰�� ������ �̵� �Ұ���
			if (p != nullptr)
			{
				break;
			}
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

	// �Ʊ��� ŷ�� üũ ���ϰ� ������ üũ�� �� �⹰�� ���θ� �����ϴ� ���� �� �� �ִ�.
	if (board->isChecked(m_eTeam))
	{
		// ŷ�� ����(üũ) ���ϴ� ��ġ ����
		for (auto iter = posList.begin(); iter != posList.end(); )
		{
			// �ӽ÷� �⹰�� �̵� ��Ų��.
			Piece* p = this->move(board, iter->first, iter->second);

			// �ӽ÷� �̵��� ���¿��� üũ ���ϴ��� Ȯ���Ѵ�.
			bool isChecked = board->isChecked(m_eTeam);

			// �ӽ÷� �̵��� �ǽ��� ���� �ڸ��� �ǵ�����.
			this->move(board, origin_x, origin_y);
			board->setPiece(p, iter->first, iter->second);

			// üũ ���ϴ� ��ġ�̸� �̵��Ұ����� ��ġ�̹Ƿ� ����
			if (isChecked)
			{
				iter = posList.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
	
	return posList;
}

std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> Queen::getAttackablePositions(Board* board)
{
	std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> posList;
	Piece* p;
	const int move_x[8] = { 0, 1, 0, -1, -1, 1, 1, -1 };
	const int move_y[8] = { -1, 0, 1, 0, -1, -1, 1, 1 };

	// �����¿�, �밢������ �̵�����
	for (int i = 0; i < 8; i++)
	{
		for (int x = move_x[i], y = move_y[i]; !((m_ix + x) < POS_A || (m_ix + x) > POS_H || (m_iy + y) < POS_8 || (m_iy + y) > POS_1); x += move_x[i], y += move_y[i])
		{
			p = board->getPiece(BOARD_POSITION_X(m_ix + x), BOARD_POSITION_Y(m_iy + y));
			// �̵��Ϸ��� ��ġ�� ����ְų� ���� ������ �̵� ����
			if (p == nullptr || m_eTeam != p->getTeam())
			{
				posList.push_back(std::make_pair(BOARD_POSITION_X(m_ix + x), BOARD_POSITION_Y(m_iy + y)));
			}

			// �̵��Ϸ��� ��ġ�� �⹰�� ������ �̵� �Ұ���
			if (p != nullptr)
			{
				break;
			}
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

Queen::Queen(LPCWSTR bitmapName, BOARD_POSITION_X x, BOARD_POSITION_Y y, TEAM team) :
	Piece(bitmapName, x, y, team)
{

}

Queen::~Queen()
{
}
