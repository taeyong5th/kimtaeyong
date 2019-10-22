#include "Tank.h"
#include "TankManager.h"

LPCWSTR Tank::getShape()
{
	return m_aAnimations[m_iAnimIndex];
}

void Tank::init(int x, int y, RECT mapRect)
{
	m_ix = x;
	m_iy = y;
	m_MapRect = mapRect;
	m_iWidth = BitmapManager::GetInstance()->getBitmap(IMG_PLAYER_TANK_D0)->getWidth() * multifly;
	m_iHeight = BitmapManager::GetInstance()->getBitmap(IMG_PLAYER_TANK_D0)->getHeight() * multifly;

	m_eState = MOVE_STATE_IDLE;
	m_ePrevState = MOVE_STATE_UP;
	m_bAutoMode = false;
	m_bShieldOn = false;

	m_iAnimIndex = 7;

	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;
	m_fAnimTick = 0.0f;
	m_fBulletTick = 0.0f;
	m_fAutoMoveTick = 0.0f;
	m_fShieldTick = 0.0f;
	m_fShieldAnimTick = 0.0f;
	m_iHP = 1;
	m_BulletManager.clear();
}

void Tank::draw()
{	// 실드를 그린다
	if (m_bShieldOn)
	{
		BitmapManager::GetInstance()->prepare(m_aShieldAnims[m_iShiledAnimIndex], m_ix, m_iy, multifly, multifly);
	}
	// 탱크를 그린다
	if (m_eTeam == TEAM_ALLY)
	{
		BitmapManager::GetInstance()->prepare(m_aAnimations[m_iAnimIndex], m_ix, m_iy, multifly, multifly);
	}
	else
	{
		BitmapManager::GetInstance()->prepare(m_aAnimations[m_iAnimIndex + 8], m_ix, m_iy, multifly, multifly);
	}	
	// 총알을 그린다.
	m_BulletManager.draw();
}

POINT Tank::update(Block* map[][MAP_HEIGHT], TankManager* enemyTanks)
{
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;

	m_fAnimTick += m_fDeltaTime;
	m_fBulletTick += m_fDeltaTime;
	m_fShieldAnimTick += m_fDeltaTime;
	m_fAutoMoveTick += m_fDeltaTime;
	if (m_bShieldOn)
	{
		m_fShieldTick += m_fDeltaTime;
	}


	// 자동으로 움직인다.
	if (m_bAutoMode)
	{
		if (m_fAutoMoveTick > 0.6f)
		{
			switch (m_aAutoMode[m_iAutoIndex])
			{
			case 0:
				m_eState = MOVE_STATE_LEFT;
				break;
			case 1:
				m_eState = MOVE_STATE_RIGHT;
				break;
			case 2:
				m_eState = MOVE_STATE_UP;
				break;
			case 3:
				m_eState = MOVE_STATE_DOWN;
				break;
			case 4:
			default:
				shootBullet();
				m_iAutoIndex = rand() % 9;
				break;
			}
			m_iAutoIndex = rand() % 9;
			m_fAutoMoveTick = 0.0f;
		}
	}

	switch (m_eState)
	{
	case MOVE_STATE_DOWN:
		m_iy += PLAYER_SPEED * m_fDeltaTime;
		m_ePrevState = m_eState;
		break;
	case MOVE_STATE_LEFT:
		m_ix -= PLAYER_SPEED * m_fDeltaTime;
		m_ePrevState = m_eState;
		break;
	case MOVE_STATE_UP:
		m_iy -= PLAYER_SPEED * m_fDeltaTime;
		m_ePrevState = m_eState;
		break;
	case MOVE_STATE_RIGHT:
		m_ix += PLAYER_SPEED * m_fDeltaTime;
		m_ePrevState = m_eState;
		break;
	}

	if (m_fAnimTick > 0.25f) // 0.15초마다 그릴 이미지 변경
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
	// 쉴드 이미지 애니메이션
	if (m_fShieldAnimTick > 0.15f)
	{
		m_iShiledAnimIndex = ++m_iShiledAnimIndex % 2;
	}
	// 실드 지속 시간 4초 후 실드꺼짐
	if (m_fShieldTick > 4.0f)
	{
		m_bShieldOn = false;
		m_fShieldTick = 0.0f;
	}

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
					m_ix = rect.right;
					break;
				case MOVE_STATE_RIGHT:
					m_ix = rect.left - m_iWidth;
					break;
				case MOVE_STATE_UP:
					m_iy = rect.bottom;
					break;
				case MOVE_STATE_DOWN:
					m_iy = rect.top - m_iHeight;
					break;
				default:
					break;
				}
			}
		}
	}
	// 맵 밖으로 나가지 않도록 한다.
	m_ix = m_ix < m_MapRect.left ? m_MapRect.left : m_ix;
	m_iy = m_iy < m_MapRect.top ? m_MapRect.top : m_iy;
	m_ix = m_ix < m_MapRect.right - m_iWidth ? m_ix : m_MapRect.right - m_iWidth;
	m_iy = m_iy < m_MapRect.bottom - m_iHeight ? m_iy : m_MapRect.bottom - m_iHeight;

	// 총알 위치를 업데이트한다.
	m_BulletManager.update(map, enemyTanks);
	
	POINT p = {m_ix, m_iy};
	return p;
}

RECT Tank::getRect()
{
	RECT rect;
	rect.top = m_iy + 3;
	rect.left = m_ix + 3;
	rect.bottom = m_iy + m_iHeight - 6;
	rect.right = m_ix + m_iWidth - 6;
	return rect;
}

bool Tank::setAutoMode(bool autoMode)
{
	m_bAutoMode = autoMode;
	return m_bAutoMode;
}

bool Tank::setShield(bool shieldOn)
{
	m_bShieldOn = shieldOn;
	return m_bShieldOn;
}

int Tank::getHP()
{
	return m_iHP;
}

void Tank::setHP(int hp)
{
	if (m_bShieldOn) return;
	hp = hp < 0 ? 0 : hp;
	m_iHP = hp;
	if (m_iHP == 0)
		m_eState = MOVE_STATE_DIE;
}


void Tank::shootBullet()
{
	m_fBulletTick += m_fDeltaTime;
	if (m_fBulletTick > 0.45f)
	{
		m_fBulletTick = 0.0f;
		Bullet bullet;
		RECT rect = getRect();
		bullet.init((rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2, m_MapRect);
		bullet.setState(m_ePrevState);
		bullet.setTeam(m_eTeam);
		m_BulletManager.add(bullet);
	}
}

Tank::Tank()
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
	
	m_aShieldAnims[0] = IMG_SHIELD_0;
	m_aShieldAnims[1] = IMG_SHIELD_1;


	for (int i = 0; i < 9; ++i)
	{
		m_aAutoMode[i] = i;
	}
}

Tank::~Tank()
{
}
