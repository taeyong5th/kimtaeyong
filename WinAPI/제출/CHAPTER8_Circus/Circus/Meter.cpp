#include "Meter.h"

void Meter::init(int x, int y)
{
	m_ix = x;
	m_iy = y;
	m_iWidth = BitmapManager::GetInstance()->getBitmap(IMG_METER)->getWidth() * m_iMultiple;
	m_iHeight = BitmapManager::GetInstance()->getBitmap(IMG_METER)->getHeight() * m_iMultiple;

	m_dwPrevTime = GetTickCount();
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = 0.0f;

	m_iNumber = (MAP_WIDTH - x) / 100;	
}

void Meter::update(int cameraX)
{
	m_iCameraX = cameraX;
}

void Meter::draw()
{
	BitmapManager::GetInstance()->prepare(IMG_METER, m_ix - m_iWidth / 2 - m_iCameraX, m_iy - m_iHeight / 2, m_iMultiple, m_iMultiple);
	m_NumberUI.draw(m_iNumber, m_ix - m_iWidth / 2 - m_iCameraX + 15, m_iy - m_iHeight / 2 + 10, m_iMultiple, 2);
}

Meter::Meter()
{
	m_iNumber = 0;
}

Meter::~Meter()
{
}
