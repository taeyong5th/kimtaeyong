#include "FireCircle.h"

RECT FireCircle::getFireRect()
{
	RECT rect;
	rect.left = m_ix;
	rect.right = m_ix + m_iWidth;
	rect.top = m_iy + m_iHeight / 2 - 11 * m_iMultiple;
	rect.bottom = m_iy + m_iHeight / 2;
	return rect;
}

void FireCircle::init(int x, int y)
{
	m_Movement = FIRE_AUTO_MOVE;

	m_ix = x;
	m_iy = y;

	m_iWidth = BitmapManager::GetInstance()->getBitmap(IMG_ENEMY_L)->getWidth() * m_iMultiple;
	m_iHeight = BitmapManager::GetInstance()->getBitmap(IMG_ENEMY_L)->getHeight() * m_iMultiple;

	m_iAnimCount = 0;

	m_RectList.clear();
	m_RectList.push_back(getFireRect());
}

void FireCircle::update(int cameraX)
{
	m_iCameraX = cameraX;
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;
	m_fAnimTick += m_fDeltaTime;
	if (m_fAnimTick > 0.15f) // 0.15초마다 그릴 이미지 변경
	{
		m_fAnimTick = 0.0f;
		m_iAnimCount = ++m_iAnimCount % 2;
	}
	// 카메라 밖(왼쪽)으로 나가면 위치를 현재화면 끝으로 옮김
	if (m_ix < cameraX)
		m_ix += WINDOW_WIDTH + 100;
	if(m_Movement == FIRE_AUTO_MOVE)
		m_ix -= m_fDeltaTime * 100;

	m_RectList.clear();
	m_RectList.push_back(getFireRect());
}

void FireCircle::draw()
{
	draw(FIRE_L);
	draw(FIRE_R);
}

void FireCircle::draw(FIRE_CIRCLE loc)
{
	switch (loc)
	{
	case FIRE_L:
		BitmapManager::GetInstance()->prepare(m_aAnimationL[m_iAnimCount], m_ix - m_iWidth / 2 - m_iCameraX, m_iy - m_iHeight / 2, m_iMultiple, m_iMultiple);
		break;
	case FIRE_R:
		BitmapManager::GetInstance()->prepare(m_aAnimationR[m_iAnimCount], m_ix + m_iWidth / 2 - m_iCameraX, m_iy - m_iHeight / 2, m_iMultiple, m_iMultiple);
		break;
	}	
}

void FireCircle::setMovement(FIRE_MOVEMENT move)
{
	m_Movement = move;
}

FireCircle::FireCircle()
{
	m_aAnimationL[0] = IMG_ENEMY_L;
	m_aAnimationL[1] = IMG_ENEMY_L2;
	m_aAnimationR[0] = IMG_ENEMY_R;
	m_aAnimationR[1] = IMG_ENEMY_R2;
}

FireCircle::~FireCircle()
{
}
