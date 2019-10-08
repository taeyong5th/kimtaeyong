#include "Piece.h"
#include "Board.h"

Piece* Piece::move(Board* board, BOARD_POSITION_X x, BOARD_POSITION_Y y)
{
	Piece* p = board->getPiece(x, y);
	board->setPiece(nullptr, m_ix, m_iy);
	m_ix = x;
	m_iy = y;
	board->setPiece(this, x, y);
	m_imoveCount++;
	return p;
}

void Piece::drawMovablePositions(HDC hdc, int x, int y, Board *board)
{
	std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> posList = getMovablePositions(board);
	float width, height;
	
	// 피스 위치에 선택된 효과를 그린다.
	width = BitmapManager::GetInstance()->getBitmap(IMG_BOARD_SELECTED)->getWidth();
	height = BitmapManager::GetInstance()->getBitmap(IMG_BOARD_SELECTED)->getHeight();
	BitmapManager::GetInstance()->prepare(hdc, IMG_BOARD_SELECTED, x + m_ix * width * BITMAP_RESIZE_RATE, y + m_iy * height * BITMAP_RESIZE_RATE, BITMAP_RESIZE_RATE, BITMAP_RESIZE_RATE);

	// 이동 가능한 좌표에 점을 그린다.
	width = BitmapManager::GetInstance()->getBitmap(IMG_BOARD_MOVABLE)->getWidth();
	height = BitmapManager::GetInstance()->getBitmap(IMG_BOARD_MOVABLE)->getHeight();
	for (auto iter = posList.begin(); iter != posList.end(); ++iter)
	{		
		BitmapManager::GetInstance()->prepare(hdc, IMG_BOARD_MOVABLE, x + iter->first * width * BITMAP_RESIZE_RATE, y + iter->second * height * BITMAP_RESIZE_RATE, BITMAP_RESIZE_RATE, BITMAP_RESIZE_RATE);
	}
}

void Piece::draw(HDC hdc, int x, int y)
{
	float width = BitmapManager::GetInstance()->getBitmap(m_strBitmapName)->getWidth();
	float height = BitmapManager::GetInstance()->getBitmap(m_strBitmapName)->getHeight();
	BitmapManager::GetInstance()->prepare(hdc, m_strBitmapName, x + m_ix * width * BITMAP_RESIZE_RATE, y + m_iy * height * BITMAP_RESIZE_RATE, BITMAP_RESIZE_RATE, BITMAP_RESIZE_RATE);
}

std::pair<BOARD_POSITION_X, BOARD_POSITION_Y> Piece::getPosition()
{
	return std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>(m_ix, m_iy);
}

TEAM Piece::getTeam()
{
	return m_eTeam;
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
