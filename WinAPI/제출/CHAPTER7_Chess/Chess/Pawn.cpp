#include "Pawn.h"
#include "Board.h"

std::vector<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> Pawn::getMovablePositions(Board* board)
{
	std::vector<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> vec;
	int direction = 1; // 아래 방향 = 1, 윗 방향 = -1
	// 백색 폰은 윗방향으로만 움직일 수 있다.
	if (m_eTeam == TEAM_WHITE) 
		direction = -1;

	// 움직인 횟수가 0이면 앞으로 최대 2칸 이동 가능
	if (m_imoveCount == 0)
	{
		vec.push_back(std::make_pair(m_ix, BOARD_POSITION_Y(m_iy + direction)));
		vec.push_back(std::make_pair(m_ix, BOARD_POSITION_Y(m_iy + direction + direction)));
	}
	else
	{
		vec.push_back(std::make_pair(m_ix, BOARD_POSITION_Y(m_iy + direction)));
	}

	// 폰은 기물이 막고 있으면 이동 불가


	return vec;
}

Pawn::Pawn(LPCWSTR bitmapName, BOARD_POSITION_X x, BOARD_POSITION_Y y, TEAM team) :
	Piece(bitmapName, x, y, team)
{

}

Pawn::~Pawn()
{
}
