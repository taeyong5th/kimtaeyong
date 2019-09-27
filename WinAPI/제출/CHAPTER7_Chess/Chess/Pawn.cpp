#include "Pawn.h"
#include "Board.h"

std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> Pawn::getMovablePositions(Board* board)
{
	std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> posList;
	Piece* p1, * p2;
	int direction = 1; // 아래 방향 = 1, 윗 방향 = -1
	// 백색 폰은 윗방향으로만 움직일 수 있다.
	if (m_eTeam == TEAM_WHITE) 
		direction = -1;

	// 움직인 횟수가 0이면 앞으로 최대 2칸 이동 가능
	if (m_imoveCount == 0)
	{
		p1 = board->getPiece(m_ix, BOARD_POSITION_Y(m_iy + direction)); // 폰이 보고 있는 방향 바로 앞
		p2 = board->getPiece(m_ix, BOARD_POSITION_Y(m_iy + direction + direction)); // 폰이 보고 있는 방향으로 두칸 앞
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
		p1 = board->getPiece(m_ix, BOARD_POSITION_Y(m_iy + direction)); // 폰이 보고 있는 방향 바로 앞
		if (p1 == nullptr)
		{
			posList.push_back(std::make_pair(m_ix, BOARD_POSITION_Y(m_iy + direction)));
		}	
	}

	// 전방에 대각선 방향에 적의 기물이 있으면 이동(잡기) 가능
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

Pawn::Pawn(LPCWSTR bitmapName, BOARD_POSITION_X x, BOARD_POSITION_Y y, TEAM team) :
	Piece(bitmapName, x, y, team)
{

}

Pawn::~Pawn()
{
}
