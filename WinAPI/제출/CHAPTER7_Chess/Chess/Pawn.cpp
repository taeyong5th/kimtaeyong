#include "Pawn.h"
#include "Board.h"

std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> Pawn::getMovablePositions(Board* board)
{
	std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> posList;
	Piece* p1, * p2;
	int direction = 1; // �Ʒ� ���� = 1, �� ���� = -1
	// ��� ���� ���������θ� ������ �� �ִ�.
	if (m_eTeam == TEAM_WHITE) 
		direction = -1;

	// ������ Ƚ���� 0�̸� ������ �ִ� 2ĭ �̵� ����
	if (m_imoveCount == 0)
	{
		p1 = board->getPiece(m_ix, BOARD_POSITION_Y(m_iy + direction)); // ���� ���� �ִ� ���� �ٷ� ��
		p2 = board->getPiece(m_ix, BOARD_POSITION_Y(m_iy + direction + direction)); // ���� ���� �ִ� �������� ��ĭ ��
		if (p1 == nullptr)
		{
			posList.push_back(std::make_pair(m_ix, BOARD_POSITION_Y(m_iy + direction)));
		}
		if(p1 == nullptr && p2 == nullptr)
		{
			posList.push_back(std::make_pair(m_ix, BOARD_POSITION_Y(m_iy + direction + direction)));
		}
	}
	else
	{
		p1 = board->getPiece(m_ix, BOARD_POSITION_Y(m_iy + direction)); // ���� ���� �ִ� ���� �ٷ� ��
		if (p1 == nullptr)
		{
			posList.push_back(std::make_pair(m_ix, BOARD_POSITION_Y(m_iy + direction)));
		}	
	}

	// ���濡 �밢�� ���⿡ ���� �⹰�� ������ �̵�(���) ����
	p1 = board->getPiece(BOARD_POSITION_X(m_ix + 1), BOARD_POSITION_Y(m_iy + direction)); 
	p2 = board->getPiece(BOARD_POSITION_X(m_ix - 1), BOARD_POSITION_Y(m_iy + direction)); 
	if (p1 != nullptr && m_eTeam != p1->getTeam())
	{
		posList.push_back(std::make_pair(BOARD_POSITION_X(m_ix + 1), BOARD_POSITION_Y(m_iy + direction)));
	}
	if (p2 != nullptr && m_eTeam != p2->getTeam())
	{
		posList.push_back(std::make_pair(BOARD_POSITION_X(m_ix - 1), BOARD_POSITION_Y(m_iy + direction)));
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
		// �̵� �� ŷ�� ����(üũ) ���ϴ� ��ġ ����
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

std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> Pawn::getAttackablePositions(Board* board)
{
	std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> posList;
	Piece* p1, * p2;
	int direction = 1; // �Ʒ� ���� = 1, �� ���� = -1
	// ��� ���� ���������θ� ������ �� �ִ�.
	if (m_eTeam == TEAM_WHITE)
		direction = -1;

	// ���濡 �밢�� ���⿡ ���� �⹰�� ������ �̵�(���) ����
	p1 = board->getPiece(BOARD_POSITION_X(m_ix + 1), BOARD_POSITION_Y(m_iy + direction));
	p2 = board->getPiece(BOARD_POSITION_X(m_ix - 1), BOARD_POSITION_Y(m_iy + direction));
	if (p1 != nullptr && m_eTeam != p1->getTeam())
	{
		posList.push_back(std::make_pair(BOARD_POSITION_X(m_ix + 1), BOARD_POSITION_Y(m_iy + direction)));
	}
	if (p2 != nullptr && m_eTeam != p2->getTeam())
	{
		posList.push_back(std::make_pair(BOARD_POSITION_X(m_ix - 1), BOARD_POSITION_Y(m_iy + direction)));
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

Pawn::Pawn(LPCWSTR bitmapName, BOARD_POSITION_X x, BOARD_POSITION_Y y, TEAM team) :
	Piece(bitmapName, x, y, team)
{

}

Pawn::~Pawn()
{
}
