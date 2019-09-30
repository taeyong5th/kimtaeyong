#include "King.h"
#include "Board.h"

std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> King::getMovablePositions(Board* board)
{
	std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> posList;
	Piece* p;
	const int move_x[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
	const int move_y[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };

	// 8개의 위치로 이동 가능
	for (int i = 0; i < 8; i++)
	{
		p = board->getPiece(BOARD_POSITION_X(m_ix + move_x[i]), BOARD_POSITION_Y(m_iy + move_y[i]));
		// p의 위치가 비어있거나 적이 있으면 이동 가능한 곳
		if (p == nullptr || m_eTeam != p->getTeam())
		{
			posList.push_back(std::make_pair(BOARD_POSITION_X(m_ix + move_x[i]), BOARD_POSITION_Y(m_iy + move_y[i])));
		}
	}

	// 체스판 밖의 이동할 수 없는 좌표를 제거
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
	
	// 킹이 공격(체크) 당하는 위치 제거
	for (auto iter = posList.begin(); iter != posList.end(); )
	{
		// 킹을 임시로 이동 시킨다.
		p = this->move(board, iter->first, iter->second);

		// 적이 공격가능한 모든 좌표를 구한다.
		std::set<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> attackedPosList = board->getAttackablePositions((TEAM)((m_eTeam + 1) % TEAM_COUNT));
		
		// 킹의 위치를 원래 자리로 되돌린다.
		this->move(board, origin_x, origin_y);
		board->setPiece(p, iter->first, iter->second);		

		// 적에 의해 공격 받는 지점이면 제거한다.
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

	// 8개의 위치로 이동 가능
	for (int i = 0; i < 8; i++)
	{
		p = board->getPiece(BOARD_POSITION_X(m_ix + move_x[i]), BOARD_POSITION_Y(m_iy + move_y[i]));
		// p의 위치가 비어있거나 적이 있으면 이동 가능한 곳
		if (p == nullptr || m_eTeam != p->getTeam())
		{
			posList.push_back(std::make_pair(BOARD_POSITION_X(m_ix + move_x[i]), BOARD_POSITION_Y(m_iy + move_y[i])));
		}
	}

	// 체스판 밖의 이동할 수 없는 좌표를 제거
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
