#include "Board.h"

void Board::setPiece(Piece* piece, BOARD_POSITION_X x, BOARD_POSITION_Y y)
{
	m_PiecesonBoard[x][y] = piece;
}

Piece* Board::getPiece(BOARD_POSITION_X x, BOARD_POSITION_Y y)
{
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
}
