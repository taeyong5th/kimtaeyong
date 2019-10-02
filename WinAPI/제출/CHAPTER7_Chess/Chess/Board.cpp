#include "Board.h"

void Board::setPiece(Piece* piece, BOARD_POSITION_X x, BOARD_POSITION_Y y)
{
	m_PiecesonBoard[x][y] = piece;
}

Piece* Board::getPiece(BOARD_POSITION_X x, BOARD_POSITION_Y y)
{
	if (x < POS_A || x > POS_H || y < POS_8 || y > POS_1)
		return nullptr;
	else
		return m_PiecesonBoard[x][y];
}

Piece* Board::getPiece(POINT point)
{
	RECT rect;
	
	float width = BitmapManager::GetInstance()->getBitmap(IMG_BOARD_WHITE)->getWidth();
	float height = BitmapManager::GetInstance()->getBitmap(IMG_BOARD_WHITE)->getHeight();

	for (UINT i = 0; i < BOARD_WIDTH; i++)
	{
		for (UINT j = 0; j < BOARD_HEIGHT; j++)
		{
			rect.left = m_ix + i * width * BITMAP_RESIZE_RATE;
			rect.top = m_iy + j * height * BITMAP_RESIZE_RATE;			
			rect.right = rect.left + width * BITMAP_RESIZE_RATE; 
			rect.bottom = rect.top + height * BITMAP_RESIZE_RATE;
			if (PtInRect(&rect, point))
			{
				return m_PiecesonBoard[i][j];
			}
		}
	}

	return nullptr;
}

void Board::draw(HDC hdc, int x, int y)
{	
	m_ix = x;
	m_iy = y;
	for (UINT i = 0; i < BOARD_WIDTH; i++)
	{
		for (UINT j = 0; j < BOARD_HEIGHT; j++)
		{
			// 보드를 그린다.
			if ((i + j) % 2 == 0)
			{
				float width = BitmapManager::GetInstance()->getBitmap(IMG_BOARD_WHITE)->getWidth();
				float height = BitmapManager::GetInstance()->getBitmap(IMG_BOARD_WHITE)->getHeight();
				BitmapManager::GetInstance()->draw(hdc, IMG_BOARD_WHITE, x + i * width * BITMAP_RESIZE_RATE, y + j * height * BITMAP_RESIZE_RATE, BITMAP_RESIZE_RATE, BITMAP_RESIZE_RATE);
			}
			else
			{
				float width = BitmapManager::GetInstance()->getBitmap(IMG_BOARD_BLACK)->getWidth();
				float height = BitmapManager::GetInstance()->getBitmap(IMG_BOARD_BLACK)->getHeight();
				BitmapManager::GetInstance()->draw(hdc, IMG_BOARD_BLACK, x + i * width * BITMAP_RESIZE_RATE, y + j * height * BITMAP_RESIZE_RATE, BITMAP_RESIZE_RATE, BITMAP_RESIZE_RATE);
			}

			// 피스를 그린다.
			if (m_PiecesonBoard[i][j] != nullptr)
			{
				m_PiecesonBoard[i][j]->draw(hdc, x, y);
			}
		}
	}
}

void Board::drawMovablePositions(HDC hdc, TEAM team)
{
	Piece* piece;
	for (UINT i = 0; i < BOARD_WIDTH; i++)
	{
		for (UINT j = 0; j < BOARD_HEIGHT; j++)
		{
			piece = m_PiecesonBoard[(BOARD_POSITION_X)i][(BOARD_POSITION_Y)j];
			if (piece != nullptr && piece->getTeam() == team)
			{
				piece->drawMovablePositions(hdc, m_ix, m_iy, this);
			}
		}
	}
}

std::pair<BOARD_POSITION_X, BOARD_POSITION_Y> Board::calcPosition(POINT point)
{
	RECT rect;

	float width = BitmapManager::GetInstance()->getBitmap(IMG_BOARD_WHITE)->getWidth();
	float height = BitmapManager::GetInstance()->getBitmap(IMG_BOARD_WHITE)->getHeight();

	for (UINT i = 0; i < BOARD_WIDTH; i++)
	{
		for (UINT j = 0; j < BOARD_HEIGHT; j++)
		{
			rect.left = m_ix + i * width * BITMAP_RESIZE_RATE;
			rect.top = m_iy + j * height * BITMAP_RESIZE_RATE;
			rect.right = rect.left + width * BITMAP_RESIZE_RATE;
			rect.bottom = rect.top + height * BITMAP_RESIZE_RATE;
			if (PtInRect(&rect, point))
			{
				return std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>((BOARD_POSITION_X)i, (BOARD_POSITION_Y)j);
			}
		}
	}

	return std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>(POS_X_INVALID, POS_Y_INVALID);
}

std::set<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> Board::getAttackablePositions(TEAM team)
{
	Piece* piece;
	std::set<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> s;

	for (UINT i = 0; i < BOARD_WIDTH; i++)
	{
		for (UINT j = 0; j < BOARD_HEIGHT; j++)
		{
			piece = m_PiecesonBoard[(BOARD_POSITION_X)i][(BOARD_POSITION_Y)j];
			if (piece == nullptr) continue;

			// team이 공격가능한 위치를 계산한다.
			if (piece->getTeam() == team)
			{
				std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> positions;
				positions = piece->getAttackablePositions(this);

				for (auto iter = positions.begin(); iter != positions.end(); ++iter)
				{
					s.insert(*iter);
				}
			}
		}
	}

	return s;
}

std::set<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> Board::getMovablePositions(TEAM team)
{
	Piece* piece;
	std::set<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> s;

	for (UINT i = 0; i < BOARD_WIDTH; i++)
	{
		for (UINT j = 0; j < BOARD_HEIGHT; j++)
		{
			piece = m_PiecesonBoard[(BOARD_POSITION_X)i][(BOARD_POSITION_Y)j];
			if (piece == nullptr) continue;

			// team이 이동가능한 위치를 계산한다.
			if (piece->getTeam() == team)
			{
				std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> positions;
				positions = piece->getMovablePositions(this);

				for (auto iter = positions.begin(); iter != positions.end(); ++iter)
				{
					s.insert(*iter);
				}
			}
		}
	}

	return s;
}

bool Board::isChecked(TEAM team)
{
	Piece* piece;
	King* king = nullptr;
	std::set<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> s;

	for (UINT i = 0; i < BOARD_WIDTH; i++)
	{
		for (UINT j = 0; j < BOARD_HEIGHT; j++)
		{
			piece = m_PiecesonBoard[(BOARD_POSITION_X)i][(BOARD_POSITION_Y)j];
			if (piece == nullptr) continue;

			// 적이 공격가능한 위치를 계산한다.
			if (piece->getTeam() != team)
			{
				std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> positions;
				positions = piece->getAttackablePositions(this);

				for (auto iter = positions.begin(); iter != positions.end(); ++iter)
				{
					s.insert(*iter);
				}
			}
			// 아군 킹의 정보를 구한다.
			else
			{
				if (king == nullptr)
					king = dynamic_cast<King*>(piece);
			}
		}
	}

	for (auto iter = s.begin(); iter != s.end(); ++iter)
	{
		if (king != nullptr && king->getPosition() == *iter)
		{
			return true;
		}
	}
	return false;
}

void Board::clear()
{
	for (UINT i = 0; i < BOARD_WIDTH; i++)
	{
		for (UINT j = 0; j < BOARD_HEIGHT; j++)
		{
			Piece* piece = m_PiecesonBoard[(BOARD_POSITION_X)i][(BOARD_POSITION_Y)j];
			if (piece == nullptr) 
				continue;
			else 
				delete piece;
		}
	}

	for (UINT i = 0; i < BOARD_WIDTH; i++)
	{
		memset(m_PiecesonBoard[i], 0, sizeof(Piece*) * BOARD_HEIGHT);
	}
}

Board::Board()
{
	m_ix = m_iy = 0;
	for (UINT i = 0; i < BOARD_WIDTH; i++)
	{
		memset(m_PiecesonBoard[i], 0, sizeof(Piece*) * BOARD_HEIGHT);
	}
	//m_PiecesonBoard[POS_H][POS_8] = new Pawn(IMG_BLACK_PAWN, POS_H, POS_8, TEAM_BLACK);
}

Board::~Board()
{
	clear();
}
