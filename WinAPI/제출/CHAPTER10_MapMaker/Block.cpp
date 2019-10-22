#include "Block.h"

Block::Block(int x, int y)
{
	m_ix = x;
	m_iy = y;
	m_iData = BLOCK_TYPE_BLANK;
}

Block::~Block()
{
}

BLOCK_TYPE Block::getData()
{
	return m_iData;
}

void Block::setData(BLOCK_TYPE data)
{
	m_iData = data;
}

void Block::toggleNext(int n)
{
	m_iData = (BLOCK_TYPE)(((int)m_iData + n + BLOCK_COUNT) % (BLOCK_COUNT));
}

void Block::draw(int top, int left)
{
	int width = BitmapManager::GetInstance()->getBitmap(IMG_BLOCK_BLANK)->getWidth();
	int height = BitmapManager::GetInstance()->getBitmap(IMG_BLOCK_BLANK)->getHeight();
	BitmapManager::GetInstance()->prepare(IMG_BLOCK_BLANK, top + m_ix * width, left + m_iy * height);
	BitmapManager::GetInstance()->prepare(getShape(), top + m_ix * width, left + m_iy * height);
}

LPCWSTR Block::getShape()
{
	switch (m_iData)
	{
	case BLOCK_TYPE_BLANK:
		return IMG_BLOCK_BLANK;
	case BLOCK_TYPE_A:
		return IMG_BLOCK_A;
	case BLOCK_TYPE_U:
		return IMG_BLOCK_U;
	case BLOCK_TYPE_L:
		return IMG_BLOCK_L;
	case BLOCK_TYPE_D:
		return IMG_BLOCK_D;
	case BLOCK_TYPE_R:
		return IMG_BLOCK_R;
	case BLOCK_TYPE_GRAY:
		return IMG_BLOCK_GRAY;
	case BLOCK_TYPE_FOREST:
		return IMG_BLOCK_FOREST;
	case BLOCK_TYPE_WATER:
		return IMG_BLOCK_WATER;
	case BLOCK_TYPE_A_HARD:
		return IMG_BLOCK_A_HARD;
	case BLOCK_TYPE_U_HARD:
		return IMG_BLOCK_U_HARD;
	case BLOCK_TYPE_L_HARD:
		return IMG_BLOCK_L_HARD;
	case BLOCK_TYPE_D_HARD:
		return IMG_BLOCK_D_HARD;
	case BLOCK_TYPE_R_HARD:
		return IMG_BLOCK_R_HARD;
	case BLOCK_TYPE_MARK:
		return IMG_BLOCK_MARK;
	case BLOCK_TYPE_FLAG:
		return IMG_BLOCK_FLAG;
	default:
		return IMG_BLOCK_BLANK;
	}
}
