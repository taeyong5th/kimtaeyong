#include "Knight.h"
#include "Board.h"

std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> Knight::getMovablePositions(Board* board)
{
	std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> posList;
	Piece* p;
	const int move_x[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
	const int move_y[8] = {-1, -2, -2, -1, 1, 2, 2, 1};

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

	// 이동 했을 때 킹이 공격(체크) 당하는 위치 제거
	for (auto iter = posList.begin(); iter != posList.end(); )
	{
		// 임시로 기물을 이동 시킨다.
		Piece* p = this->move(board, iter->first, iter->second);

		// 임시로 이동한 상태에서 체크 당하는지 확인한다.
		bool isChecked = board->isChecked(m_eTeam);

		// 임시로 이동한 피스를 원래 자리로 되돌린다.
		this->move(board, origin_x, origin_y);
		board->setPiece(p, iter->first, iter->second);

		// 체크 당하는 위치이면 이동불가능한 위치이므로 제외
		if (isChecked)
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

std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> Knight::getAttackablePositions(Board* board)
{
	std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> posList;
	Piece* p;
	const int move_x[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
	const int move_y[8] = { -1, -2, -2, -1, 1, 2, 2, 1 };

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

Knight::Knight(LPCWSTR bitmapName, BOARD_POSITION_X x, BOARD_POSITION_Y y, TEAM team) :
	Piece(bitmapName, x, y, team)
{

}

Knight::~Knight()
{
}
