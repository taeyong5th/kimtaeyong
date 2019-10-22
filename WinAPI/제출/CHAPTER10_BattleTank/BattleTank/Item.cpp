#include "Item.h"

LPCWSTR Item::getShape()
{
	return IMG_ITEM;
}

void Item::init(int x, int y, RECT mapRect)
{
	m_ix = x;
	m_iy = y;
	m_MapRect = mapRect;
	m_iWidth = BitmapManager::GetInstance()->getBitmap(IMG_ITEM)->getWidth();
	m_iHeight = BitmapManager::GetInstance()->getBitmap(IMG_ITEM)->getHeight();
}

void Item::draw()
{
	BitmapManager::GetInstance()->prepare(IMG_ITEM, m_ix, m_iy);
}

RECT Item::getRect()
{
	RECT rect;
	rect.top = m_iy;
	rect.left = m_ix;
	rect.bottom = m_iy + m_iHeight;
	rect.right = m_ix + m_iWidth;
	return rect;
}

Item::Item()
{
}

Item::~Item()
{
}
