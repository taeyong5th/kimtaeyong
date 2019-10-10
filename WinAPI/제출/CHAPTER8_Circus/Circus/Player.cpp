#include "Player.h"


RECT Player::getRect()
{
	return m_Rect;
}

void Player::setState(PLAYER_STATE state)
{
	if (m_eState != PLAYER_STATE_JUMP)
		m_eState = state;
}

void Player::update(int x, int y)
{

	m_ix = x;
	m_iy = y;
	m_iWidth = BitmapManager::GetInstance()->getBitmap(IMG_PLAYER1)->getWidth() * m_iMultiple;
	m_iHeight = BitmapManager::GetInstance()->getBitmap(IMG_PLAYER1)->getHeight() * m_iMultiple;

	m_Rect.left = m_ix - m_iWidth / 2;
	m_Rect.right = m_Rect.left + m_iWidth;
	m_Rect.top = m_iy + m_iHeight / 4;
	m_Rect.bottom = m_iy + m_iHeight / 2;
}

void Player::draw()
{
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;

	static int animCount = 0;
	switch (m_eState)
	{
	case PLAYER_STATE_IDLE:
		BitmapManager::GetInstance()->prepare(m_aMoveAnimation[0], m_ix - m_iWidth / 2, m_iy - m_iHeight / 2, m_iMultiple, m_iMultiple);
		break;
	case PLAYER_STATE_MOVE:
		m_fMoveAnimTick += m_fDeltaTime;
		if (m_fMoveAnimTick > 0.15f) // 0.15초마다 그릴 이미지 변경
		{
			m_fMoveAnimTick = 0.0f;
			animCount = ++animCount % 3;
		}
		BitmapManager::GetInstance()->prepare(m_aMoveAnimation[animCount], m_ix - m_iWidth / 2, m_iy - m_iHeight / 2, m_iMultiple, m_iMultiple);
		break;
	case PLAYER_STATE_JUMP:
		m_fJumpTick += m_fDeltaTime;
		if (m_fJumpTick < 1.2f) // 1.2초 동안 점프
		{
			float temp = sinf(m_fJumpTick / 1.2f * PI) * 190;
			BitmapManager::GetInstance()->prepare(m_aMoveAnimation[2], m_ix - m_iWidth / 2, m_iy - m_iHeight / 2 - temp, m_iMultiple, m_iMultiple);
		}
		else
		{
			m_fJumpTick = 0.0f;
			m_eState = PLAYER_STATE_IDLE;
			BitmapManager::GetInstance()->prepare(m_aMoveAnimation[2], m_ix - m_iWidth / 2, m_iy - m_iHeight / 2, m_iMultiple, m_iMultiple);
		}
		break;
	case PLAYER_STATE_DIE:
		BitmapManager::GetInstance()->prepare(IMG_PLAYER_DIE, m_ix - m_iWidth / 2, m_iy - m_iHeight / 2, m_iMultiple, m_iMultiple);
		break;
	case PLAYER_STATE_WIN:
		m_fMoveAnimTick += m_fDeltaTime;
		if (m_fMoveAnimTick > 0.15f) // 0.15초마다 그릴 이미지 변경
		{
			m_fMoveAnimTick = 0.0f;
			animCount = ++animCount % 2;
		}
		BitmapManager::GetInstance()->prepare(m_aWinAnimation[animCount], m_ix - m_iWidth / 2, m_iy - m_iHeight / 2 - sinf(m_fJumpTick / 1.2f * PI) * 190, m_iMultiple, m_iMultiple);
		break;
	default:
		break;
	}
}

void Player::init(int x, int y)
{
	m_ix = x;
	m_iy = y;	
	//m_iWidth = BitmapManager::GetInstance()->getBitmap(IMG_PLAYER1)->getWidth() * m_iMultiple;
	//m_iHeight = BitmapManager::GetInstance()->getBitmap(IMG_PLAYER1)->getHeight() * m_iMultiple;

	m_Rect.left = m_ix - m_iWidth / 2;
	m_Rect.right = m_Rect.left + m_iWidth;
	m_Rect.top = m_iy + m_iHeight / 4;
	m_Rect.bottom = m_iy + m_iHeight / 2;

	m_eState = PLAYER_STATE_IDLE;

	m_fMoveAnimTick = 0.0f;
	m_fJumpTick = 0.0f;
	m_dwPrevTime = GetTickCount();
	m_dwCurTime = GetTickCount();
}

Player::Player()
{
	init(0, 0);
	m_aMoveAnimation[0] = IMG_PLAYER1;
	m_aMoveAnimation[1] = IMG_PLAYER2;
	m_aMoveAnimation[2] = IMG_PLAYER3;
	m_aWinAnimation[0] = IMG_PLAYER_WIN1;
	m_aWinAnimation[1] = IMG_PLAYER_WIN2;
}

Player::~Player()
{
}
