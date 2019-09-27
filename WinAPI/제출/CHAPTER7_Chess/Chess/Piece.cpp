#include "Piece.h"
#include "Board.h"

bool Piece::move(Board* board, BOARD_POSITION_X x, BOARD_POSITION_Y y)
{
	board->setPiece(nullptr, m_ix, m_iy);
	m_ix = x;
	m_iy = y;
	board->setPiece(this, x, y);
	m_imoveCount++;
	return false;
}

void Piece::drawMovablePositions(HDC hdc, int x, int y, Board *board)
{
	std::vector<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> vec = getMovablePositions(board);

	float width = BitmapManager::GetInstance()->getBitmap(IMG_BOARD_MOVABLE)->getWidth();
	float height = BitmapManager::GetInstance()->getBitmap(IMG_BOARD_MOVABLE)->getHeight();

	for (int i = 0; i < vec.size(); i++)
	{		
		BitmapManager::GetInstance()->draw(hdc, IMG_BOARD_MOVABLE, x + vec[i].first * width * BITMAP_RESIZE_RATE, y + vec[i].second * height * BITMAP_RESIZE_RATE, BITMAP_RESIZE_RATE, BITMAP_RESIZE_RATE);
	}
}

void Piece::draw(HDC hdc, int x, int y)
{
	float width = BitmapManager::GetInstance()->getBitmap(m_strBitmapName)->getWidth();
	float height = BitmapManager::GetInstance()->getBitmap(m_strBitmapName)->getHeight();
	BitmapManager::GetInstance()->draw(hdc, m_strBitmapName, x + m_ix * width * BITMAP_RESIZE_RATE, y + m_iy * height * BITMAP_RESIZE_RATE, BITMAP_RESIZE_RATE, BITMAP_RESIZE_RATE);
}

std::pair<BOARD_POSITION_X, BOARD_POSITION_Y> Piece::getPosition()
{
	return std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>(m_ix, m_iy);
}

Piece::Piece(LPCWSTR bitmapName, BOARD_POSITION_X x, BOARD_POSITION_Y y, TEAM team) :
	m_strBitmapName(bitmapName), m_ix(x), m_iy(y), m_eTeam(team)
{
	m_bChoose = false;
	m_imoveCount = 0;
}

Piece::~Piece()
{
}
