#include "Bullet.h"

LPCWSTR Bullet::getShape()
{
	switch (m_eState)
	{
	case MOVE_STATE_IDLE:
		break;
	case MOVE_STATE_LEFT:
		return m_aBulletImage[0];
	case MOVE_STATE_DOWN:
		return m_aBulletImage[1];
	case MOVE_STATE_RIGHT:
		return m_aBulletImage[2];
	case MOVE_STATE_UP:
		return m_aBulletImage[3];
	case MOVE_STATE_EXPLOSION:
		return m_aAnimations[m_iAnimIndex];
		break;
	default:
		break;
	}
	return m_aBulletImage[3];
}

void Bullet::init(int x, int y, RECT mapRect)
{
	m_ix = x;
	m_iy = y;
	m_MapRect = mapRect;
	m_iWidth = BitmapManager::GetInstance()->getBitmap(getShape())->getWidth() * multifly;
	m_iHeight = BitmapManager::GetInstance()->getBitmap(getShape())->getHeight() * multifly;

	m_eState = MOVE_STATE_IDLE;

	m_iAnimIndex = 0;

	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;
	m_fAnimTick = 0.0f;
}

void Bullet::draw()
{
	switch (m_eState)
	{
	case MOVE_STATE_IDLE:
		break;
	case MOVE_STATE_LEFT:
	case MOVE_STATE_DOWN:
	case MOVE_STATE_RIGHT:
	case MOVE_STATE_UP:
		BitmapManager::GetInstance()->prepare(getShape(), m_ix, m_iy, multifly, multifly);
		break;
	case MOVE_STATE_EXPLOSION:
		BitmapManager::GetInstance()->prepare(getShape(), m_ix - m_iWidth / 2, m_iy - m_iHeight / 2, multifly, multifly);
		break;
	default:
		break;
	}
}

void Bullet::update()
{
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;

	m_fAnimTick += m_fDeltaTime;
	if (m_fAnimTick > 0.15f && m_eState == MOVE_STATE_EXPLOSION) // 0.15초마다 그릴 이미지 변경
	{
		// 폭발 애니메이션 종료
		if (m_iAnimIndex >= 4)
		{
			m_eState = MOVE_STATE_DIE;
		}

		m_iAnimIndex = m_iAnimIndex++ % 5;
		m_iWidth = BitmapManager::GetInstance()->getBitmap(getShape())->getWidth() * multifly;
		m_iHeight = BitmapManager::GetInstance()->getBitmap(getShape())->getHeight() * multifly;
		m_fAnimTick = 0.0f;
	}	

	switch (m_eState)
	{
	case MOVE_STATE_UP:
		m_iy -= m_fDeltaTime * 200;
		break;
	case MOVE_STATE_LEFT:
		m_ix -= m_fDeltaTime * 200;
		break;
	case MOVE_STATE_DOWN:
		m_iy += m_fDeltaTime * 200;
		break;
	case MOVE_STATE_RIGHT:
		m_ix += m_fDeltaTime * 200;
		break;
	default:
		break;
	}
}


RECT Bullet::getRect()
{
	RECT rect;
	rect.top = m_iy;
	rect.left = m_ix;
	rect.bottom = m_iy + m_iHeight;
	rect.right = m_ix + m_iWidth;
	return rect;
}

Bullet::Bullet()
{
	m_aAnimations[0] = IMG_EXPLOSION_0;
	m_aAnimations[1] = IMG_EXPLOSION_1;
	m_aAnimations[2] = IMG_EXPLOSION_2;
	m_aAnimations[3] = IMG_EXPLOSION_3;
	m_aAnimations[4] = IMG_EXPLOSION_4;

	m_aBulletImage[0] = IMG_BULLET_L;// ;
	m_aBulletImage[1] = IMG_BULLET_D;
	m_aBulletImage[2] = IMG_BULLET_R;
	m_aBulletImage[3] = IMG_BULLET_U;
}

Bullet::~Bullet()
{
}
