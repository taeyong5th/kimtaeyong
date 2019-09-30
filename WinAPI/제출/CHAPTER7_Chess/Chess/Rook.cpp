#include "Rook.h"
#include "Board.h"

std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> Rook::getMovablePositions(Board* board)
{
	std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> posList;
	Piece* p;
	const int move_x[4] = {0, 1, 0, -1};
	const int move_y[4] = {-1, 0, 1, 0};

	// 상하좌우 이동가능
	for (int i = 0; i < 4; i++)
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


Rook::Rook(LPCWSTR bitmapName, BOARD_POSITION_X x, BOARD_POSITION_Y y, TEAM team) :
	Piece(bitmapName, x, y, team)
{

}

Rook::~Rook()
{
}
