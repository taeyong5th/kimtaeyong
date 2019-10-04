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

	BOARD_POSITION_X origin_x = m_ix;
	BOARD_POSITION_Y origin_y = m_iy;

	// 아군의 킹이 체크 당하고 있으면 체크를 건 기물의 진로를 차단하는 수만 둘 수 있다.
	if (board->isChecked(m_eTeam))
	{
		// 이동 후 킹이 공격(체크) 당하는 위치 제거
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

std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> Pawn::getAttackablePositions(Board* board)
{
	std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> posList;
	Piece* p1, * p2;
	int direction = 1; // 아래 방향 = 1, 윗 방향 = -1
	// 백색 폰은 윗방향으로만 움직일 수 있다.
	if (m_eTeam == TEAM_WHITE)
		direction = -1;

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
