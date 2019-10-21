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

void Block::draw()
{
	BitmapManager::GetInstance()->prepare(IMG_BLOCK_BLANK, m_ix, m_iy, multifly, multifly);
	BitmapManager::GetInstance()->prepare(getShape(), m_ix, m_iy, multifly, multifly);	
}

RECT Block::getRect()
{
	RECT rect;
	rect.top = m_iy;
	rect.left = m_ix;
	rect.bottom = m_iy + m_iHeight;
	rect.right = m_ix + m_iWidth;
	switch (m_iData)
	{
	case BLOCK_TYPE_A:
	case BLOCK_TYPE_A_HARD:
		break;
	case BLOCK_TYPE_U:
	case BLOCK_TYPE_U_HARD:
		rect.bottom -= m_iHeight / 2;
		break;
	case BLOCK_TYPE_L_HARD:
	case BLOCK_TYPE_L:
		rect.right -= m_iWidth / 2;
		break;
	case BLOCK_TYPE_D:
	case BLOCK_TYPE_D_HARD:
		rect.top += m_iHeight / 2;
		break;
	case BLOCK_TYPE_R:
	case BLOCK_TYPE_R_HARD:	
		rect.left += m_iWidth / 2;
		//rect.top += m_iHeight / 2;
		break;
	case BLOCK_TYPE_BLANK:
	case BLOCK_TYPE_GRAY:
	case BLOCK_TYPE_FOREST:
	case BLOCK_TYPE_WATER:
	case BLOCK_TYPE_MARK:
	case BLOCK_TYPE_FLAG:
	default:
		ZeroMemory(&rect, sizeof(RECT));
		break;
	}

	return rect;
}

void Block::init()
{
	m_iWidth = BitmapManager::GetInstance()->getBitmap(IMG_BLOCK_BLANK)->getWidth() * multifly;
	m_iHeight = BitmapManager::GetInstance()->getBitmap(IMG_BLOCK_BLANK)->getHeight() * multifly;
	m_iData = BLOCK_TYPE_BLANK;
}

void Block::Attacked(MOVE_STATE from)
{	
	if (m_iData == BLOCK_TYPE_A)
	{
		switch (from)
		{
		case MOVE_STATE_RIGHT:
			m_iData = BLOCK_TYPE_R;
			break;
		case MOVE_STATE_LEFT:
			m_iData = BLOCK_TYPE_L;
			break;
		case MOVE_STATE_UP:
			m_iData = BLOCK_TYPE_U;
			break;
		case MOVE_STATE_DOWN:
			m_iData = BLOCK_TYPE_D;
			break;
		default:
			break;
		}
	}
	else if (m_iData == BLOCK_TYPE_A_HARD)
	{
		switch (from)
		{
		case MOVE_STATE_RIGHT:
			m_iData = BLOCK_TYPE_R_HARD;
			break;
		case MOVE_STATE_LEFT:
			m_iData = BLOCK_TYPE_L_HARD;
			break;
		case MOVE_STATE_UP:
			m_iData = BLOCK_TYPE_U_HARD;
			break;
		case MOVE_STATE_DOWN:
			m_iData = BLOCK_TYPE_D_HARD;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (from)
		{
		case MOVE_STATE_RIGHT:
		case MOVE_STATE_LEFT:
		case MOVE_STATE_UP:
		case MOVE_STATE_DOWN:
			m_iData = BLOCK_TYPE_BLANK;
			break;
		default:
			break;
		}
	}
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
