#include "Goal.h"

RECT Goal::getGoalRect()
{
	RECT rect;
	rect.left = m_ix - m_iWidth / 2;
	rect.right = rect.left + m_iWidth;
	rect.top = m_iy - m_iHeight / 2;
	rect.bottom = rect.top + m_iHeight;
	return rect;
}

void Goal::init(int x, int y)
{
	m_ix = x;
	m_iy = y;

	m_iWidth = BitmapManager::GetInstance()->getBitmap(IMG_GOAL)->getWidth() * m_iMultiple;
	m_iHeight = BitmapManager::GetInstance()->getBitmap(IMG_GOAL)->getHeight() * m_iMultiple;

	m_dwPrevTime = GetTickCount();
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = 0.0f;
}

void Goal::update(int cameraX)
{
	m_iCameraX = cameraX;

	m_RectList.clear();
	m_RectList.push_back(getGoalRect());
}

void Goal::draw()
{
	BitmapManager::GetInstance()->prepare(IMG_GOAL, m_ix - m_iWidth / 2 - m_iCameraX, m_iy - m_iHeight / 2, m_iMultiple, m_iMultiple);
}

Goal::Goal()
{
	
}

Goal::~Goal()
{
}
