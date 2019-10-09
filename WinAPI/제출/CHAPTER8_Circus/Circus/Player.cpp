#include "Player.h"

void Player::setState(PLAYER_STATE state)
{
	if(m_eState != PLAYER_STATE_JUMP)
		m_eState = state;
}

void Player::update(int x, int y)
{
	m_ix = x;
	m_iy = y;

	int width = BitmapManager::GetInstance()->getBitmap(IMG_PLAYER1)->getWidth() * multiple;
	int height = BitmapManager::GetInstance()->getBitmap(IMG_PLAYER1)->getHeight() * multiple;
	
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;

	static int animCount = 0;
	switch (m_eState)
	{
	case PLAYER_STATE_IDLE:
		BitmapManager::GetInstance()->prepare(moveAnimation[0], m_ix - width / 2, m_iy - height / 2, multiple, multiple);
		break;
	case PLAYER_STATE_MOVE:
		m_fMoveAnimTick += m_fDeltaTime;
		if (m_fMoveAnimTick > 0.15f) // 0.15초마다 그릴 이미지 변경
		{
			m_fMoveAnimTick = 0.0f;
			animCount = ++animCount % 3;
		}
		BitmapManager::GetInstance()->prepare(moveAnimation[animCount], m_ix - width / 2, m_iy - height / 2, multiple, multiple);
		break;
	case PLAYER_STATE_JUMP:
		m_fJumpTick += m_fDeltaTime;
		if (m_fJumpTick < 1.0f) // 1초 동안 점프
		{
			float temp = sinf(m_fJumpTick * PI) * 120;
			BitmapManager::GetInstance()->prepare(moveAnimation[2], m_ix - width / 2, m_iy - height / 2 - temp, multiple, multiple);
		}
		else
		{
			m_fJumpTick = 0.0f;
			m_eState = PLAYER_STATE_IDLE;
			BitmapManager::GetInstance()->prepare(moveAnimation[2], m_ix - width / 2, m_iy - height / 2, multiple, multiple);
		}
		break;
	case PLAYER_STATE_DIE:
		break;
	default:
		break;
	}

	
}

void Player::init(int x, int y)
{
	m_ix = x;
	m_iy = y;
	m_eState = PLAYER_STATE_IDLE;

	m_fMoveAnimTick = 0.0f;
	m_fJumpTick = 0.0f;
	m_dwPrevTime = GetTickCount();
	m_dwCurTime = GetTickCount();
}

Player::Player()
{
	init(0, 0);
	moveAnimation[0] = IMG_PLAYER1;
	moveAnimation[1] = IMG_PLAYER2;
	moveAnimation[2] = IMG_PLAYER3;
}

Player::~Player()
{
}
