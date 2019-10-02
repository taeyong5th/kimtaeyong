#include "Queen.h"
#include "Board.h"

std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> Queen::getMovablePositions(Board* board)
{
	std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> posList;
	Piece* p;
	const int move_x[8] = { 0, 1, 0, -1, -1, 1, 1, -1};
	const int move_y[8] = { -1, 0, 1, 0, -1, -1, 1, 1};

	// 상하좌우, 대각선으로 이동가능
	for (int i = 0; i < 8; i++)
	{
		for (int x = move_x[i], y = move_y[i]; !((m_ix + x) < POS_A || (m_ix + x) > POS_H || (m_iy + y) < POS_8 || (m_iy + y) > POS_1); x += move_x[i], y += move_y[i])
		{
			p = board->getPiece(BOARD_POSITION_X(m_ix + x), BOARD_POSITION_Y(m_iy + y));
			// 이동하려는 위치가 비어있거나 적이 있으면 이동 가능
			if (p == nullptr || m_eTeam != p->getTeam())
			{
				posList.push_back(std::make_pair(BOARD_POSITION_X(m_ix + x), BOARD_POSITION_Y(m_iy + y)));
			}

			// 이동하려는 위치에 기물이 있으면 이동 불가능
			if (p != nullptr)
			{
				break;
			}
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

	// 아군의 킹이 체크 당하고 있으면 체크를 건 기물의 진로를 차단하는 수만 둘 수 있다.
	if (board->isChecked(m_eTeam))
	{
		// 킹이 공격(체크) 당하는 위치 제거
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
	}
	
	return posList;
}

std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> Queen::getAttackablePositions(Board* board)
{
	std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> posList;
	Piece* p;
	const int move_x[8] = { 0, 1, 0, -1, -1, 1, 1, -1 };
	const int move_y[8] = { -1, 0, 1, 0, -1, -1, 1, 1 };

	// 상하좌우, 대각선으로 이동가능
	for (int i = 0; i < 8; i++)
	{
		for (int x = move_x[i], y = move_y[i]; !((m_ix + x) < POS_A || (m_ix + x) > POS_H || (m_iy + y) < POS_8 || (m_iy + y) > POS_1); x += move_x[i], y += move_y[i])
		{
			p = board->getPiece(BOARD_POSITION_X(m_ix + x), BOARD_POSITION_Y(m_iy + y));
			// 이동하려는 위치가 비어있거나 적이 있으면 이동 가능
			if (p == nullptr || m_eTeam != p->getTeam())
			{
				posList.push_back(std::make_pair(BOARD_POSITION_X(m_ix + x), BOARD_POSITION_Y(m_iy + y)));
			}

			// 이동하려는 위치에 기물이 있으면 이동 불가능
			if (p != nullptr)
			{
				break;
			}
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

Queen::Queen(LPCWSTR bitmapName, BOARD_POSITION_X x, BOARD_POSITION_Y y, TEAM team) :
	Piece(bitmapName, x, y, team)
{

}

Queen::~Queen()
{
}
