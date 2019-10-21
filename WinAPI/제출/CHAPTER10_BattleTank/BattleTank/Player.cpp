#include "Player.h"

LPCWSTR Player::getShape()
{
	return m_aAnimations[m_iAnimIndex];
}

void Player::init(int x, int y, RECT mapRect)
{
	m_ix = x;
	m_iy = y;
	m_MapRect = mapRect;
	m_iWidth = BitmapManager::GetInstance()->getBitmap(IMG_PLAYER_TANK_D0)->getWidth() * multifly;
	m_iHeight = BitmapManager::GetInstance()->getBitmap(IMG_PLAYER_TANK_D0)->getHeight() * multifly;

	m_eState = MOVE_STATE_IDLE;

	m_iAnimIndex = 7;

	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;
	m_fAnimTick = 0.0f;
	m_fBulletTime = 0.0f;

	m_BulletManager.clear();
}

void Player::draw()
{	
	if (m_eTeam == TEAM_ALLY)
	{
		BitmapManager::GetInstance()->prepare(m_aAnimations[m_iAnimIndex], m_ix, m_iy, multifly, multifly);
	}
	else
	{
		BitmapManager::GetInstance()->prepare(m_aAnimations[m_iAnimIndex + 8], m_ix, m_iy, multifly, multifly);
	}	
	m_BulletManager.draw();
}

void Player::update(int& x, int& y, Block* map[][MAP_HEIGHT])
{
	m_ix = x;
	m_iy = y;

	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;

	m_fAnimTick += m_fDeltaTime;
	m_fBulletTime += m_fDeltaTime;

	if (m_fAnimTick > 0.15f) // 0.15초마다 그릴 이미지 변경
	{
		switch (m_eState)
		{
		case MOVE_STATE_LEFT:
			m_iAnimIndex = ++m_iAnimIndex % 2;
			break;
		case MOVE_STATE_DOWN:
			m_iAnimIndex = ++m_iAnimIndex % 2 + 2;
			break;
		case MOVE_STATE_RIGHT:
			m_iAnimIndex = ++m_iAnimIndex % 2 + 4;
			break;
		case MOVE_STATE_UP:
			m_iAnimIndex = ++m_iAnimIndex % 2 + 6;
			break;
		case MOVE_STATE_IDLE:
		default:
			break;
		}
		m_fAnimTick = 0.0f;
	}


	// 맵 밖으로 나가지 않도록 한다.
	m_ix = m_ix < m_MapRect.left ? m_MapRect.left : m_ix;
	m_iy = m_iy < m_MapRect.top ? m_MapRect.top : m_iy;
	m_ix = m_ix < m_MapRect.right - m_iWidth ? m_ix : m_MapRect.right - m_iWidth;
	m_iy = m_iy < m_MapRect.bottom - m_iHeight ? m_iy : m_MapRect.bottom - m_iHeight;

	// 블럭과의 충돌을 검사하고 위치를 보정한다.
	RECT rect;
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (IntersectRect(&rect, &map[i][j]->getRect(), &getRect()))
			{
				switch (m_eState)
				{
				case MOVE_STATE_IDLE:
					break;	
				case MOVE_STATE_LEFT:
					x = rect.right;
					break;
				case MOVE_STATE_RIGHT:
					x = rect.left - m_iWidth;
					break;
				case MOVE_STATE_UP:
					y = rect.bottom;
					break;
				case MOVE_STATE_DOWN:
					y = rect.top - m_iHeight;
					break;
				default:
					break;
				}
			}
		}
	}

	// 총알 위치를 업데이트한다.
	m_BulletManager.update(map);
}

void Player::setState(MOVE_STATE state)
{
	m_eState = state;
}

MOVE_STATE Player::getState()
{
	return m_eState;
}

RECT Player::getRect()
{
	RECT rect;
	rect.top = m_iy + 3;
	rect.left = m_ix + 3;
	rect.bottom = m_iy + m_iHeight - 6;
	rect.right = m_ix + m_iWidth - 6;
	return rect;
}


void Player::shootBullet()
{
	if (m_fBulletTime > 0.25f)
	{
		m_fBulletTime = 0.0f;
		Bullet bullet;
		RECT rect = getRect();
		bullet.init((rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2, m_MapRect);
		bullet.setState(m_eState);
		m_BulletManager.add(bullet);
	}
}

Player::Player()
{
	m_aAnimations[0] = IMG_PLAYER_TANK_L0;
	m_aAnimations[1] = IMG_PLAYER_TANK_L1;
	m_aAnimations[2] = IMG_PLAYER_TANK_D0;
	m_aAnimations[3] = IMG_PLAYER_TANK_D1;
	m_aAnimations[4] = IMG_PLAYER_TANK_R0;
	m_aAnimations[5] = IMG_PLAYER_TANK_R1;
	m_aAnimations[6] = IMG_PLAYER_TANK_U0;
	m_aAnimations[7] = IMG_PLAYER_TANK_U1;
	
	m_aAnimations[8] = IMG_ENEMY_TANK_L0;
	m_aAnimations[9] = IMG_ENEMY_TANK_L1;
	m_aAnimations[10] = IMG_ENEMY_TANK_D0;
	m_aAnimations[11] = IMG_ENEMY_TANK_D1;
	m_aAnimations[12] = IMG_ENEMY_TANK_R0;
	m_aAnimations[13] = IMG_ENEMY_TANK_R1;
	m_aAnimations[14] = IMG_ENEMY_TANK_U0;
	m_aAnimations[15] = IMG_ENEMY_TANK_U1;
}

Player::~Player()
{
}
