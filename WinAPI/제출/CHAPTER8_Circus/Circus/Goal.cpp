#include "Goal.h"

void Goal::init(int x, int y)
{
	m_ix = x;
	m_iy = y;

	m_iWidth = BitmapManager::GetInstance()->getBitmap(IMG_GOAL)->getWidth() * m_iMultiple;
	m_iHeight = BitmapManager::GetInstance()->getBitmap(IMG_GOAL)->getHeight() * m_iMultiple;

	m_Rect.left = m_ix - m_iWidth / 2;
	m_Rect.right = m_Rect.left + m_iWidth;
	m_Rect.top = m_iy - m_iHeight / 2;
	m_Rect.bottom = m_Rect.top + m_iHeight;
}

void Goal::update(int x, int y)
{
	init(x, y);
}

void Goal::draw()
{
	BitmapManager::GetInstance()->prepare(IMG_GOAL, m_ix - m_iWidth / 2, m_iy - m_iHeight / 2, m_iMultiple, m_iMultiple);
}

RECT Goal::getRect()
{
	return m_Rect;
}

Goal::Goal()
{
	
}

Goal::~Goal()
{
}
