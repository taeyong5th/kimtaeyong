#include "Player.h"

void Player::setPosition(int player_x)
{
	m_ix = player_x;
	m_RectList.clear();
	m_RectList.push_back(getLionRect());
	m_RectList.push_back(getPlayerRect());
}

void Player::setState(PLAYER_STATE state)
{
	if (m_eState == PLAYER_STATE_WIN || m_eState == PLAYER_STATE_DIE)
		return;
	if (m_eState != PLAYER_STATE_JUMP)
		m_eState = state;
	if (state == PLAYER_STATE_WIN || state == PLAYER_STATE_DIE)
	{
		m_eState = state;
	}
}

void Player::update(int camera_x)
{
	m_iCameraX = camera_x;

	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;

	//m_ix = m_iCameraX + 140;

	m_iWidth = BitmapManager::GetInstance()->getBitmap(IMG_PLAYER1)->getWidth() * m_iMultiple;
	m_iHeight = BitmapManager::GetInstance()->getBitmap(IMG_PLAYER1)->getHeight() * m_iMultiple;

	m_RectList.clear();
	m_RectList.push_back(getLionRect());
	m_RectList.push_back(getPlayerRect());
}

void Player::draw()
{

	static int animCount = 0;
	static int originY;
	if (m_eState == PLAYER_STATE_IDLE) originY = m_iy;

	switch (m_eState)
	{
	case PLAYER_STATE_IDLE:
		BitmapManager::GetInstance()->prepare(m_aMoveAnimation[0], m_ix - m_iWidth / 2 - m_iCameraX, m_iy - m_iHeight / 2, m_iMultiple, m_iMultiple);
		break;
	case PLAYER_STATE_MOVE:
		m_fMoveAnimTick += m_fDeltaTime;
		if (m_fMoveAnimTick > 0.15f) // 0.15초마다 그릴 이미지 변경
		{
			m_fMoveAnimTick = 0.0f;
			animCount = ++animCount % 3;
		}
		BitmapManager::GetInstance()->prepare(m_aMoveAnimation[animCount], m_ix - m_iWidth / 2 - m_iCameraX, m_iy - m_iHeight / 2, m_iMultiple, m_iMultiple);
		break;
	case PLAYER_STATE_JUMP:
		m_fJumpTick += m_fDeltaTime;
		if (m_fJumpTick < 1.2f) // 1.2초 동안 점프
		{
			float temp = sinf(m_fJumpTick / 1.2f * PI) * 190;
			m_iy = originY - temp;

			m_RectList.clear();
			m_RectList.push_back(getLionRect());
			m_RectList.push_back(getPlayerRect());
			BitmapManager::GetInstance()->prepare(m_aMoveAnimation[2], m_ix - m_iWidth / 2 - m_iCameraX, m_iy - m_iHeight / 2, m_iMultiple, m_iMultiple);
		}
		else
		{
			m_iy = originY;
			m_fJumpTick = 0.0f;
			m_eState = PLAYER_STATE_IDLE;
			BitmapManager::GetInstance()->prepare(m_aMoveAnimation[2], m_ix - m_iWidth / 2 - m_iCameraX, m_iy - m_iHeight / 2, m_iMultiple, m_iMultiple);
		}
		break;
	case PLAYER_STATE_DIE:
		BitmapManager::GetInstance()->prepare(IMG_PLAYER_DIE, m_ix - m_iWidth / 2 - m_iCameraX, m_iy - m_iHeight / 2, m_iMultiple, m_iMultiple);
		break;
	case PLAYER_STATE_WIN:
		m_fMoveAnimTick += m_fDeltaTime;
		if (m_fMoveAnimTick > 0.15f) // 0.15초마다 그릴 이미지 변경
		{
			m_fMoveAnimTick = 0.0f;
			animCount = ++animCount % 2;
		}
		BitmapManager::GetInstance()->prepare(m_aWinAnimation[animCount], m_ix - m_iWidth / 2 - m_iCameraX, m_iy - m_iHeight / 2, m_iMultiple, m_iMultiple);
		break;
	default:
		break;
	}
}

RECT Player::getPlayerRect()
{
	RECT rect;
	rect.left = m_ix - m_iWidth / 7;
	rect.right = m_ix + m_iWidth / 7;
	rect.top = m_iy - m_iHeight / 2;
	rect.bottom = m_iy;
	return rect;
}

RECT Player::getLionRect()
{
	RECT rect;
	rect.left = m_ix - m_iWidth / 2;
	rect.right = rect.left + m_iWidth;
	rect.top = m_iy;
	rect.bottom = m_iy + m_iHeight / 2;
	return rect;
}

void Player::init(int x, int y)
{
	m_ix = x;
	m_iy = y;	
	m_iWidth = BitmapManager::GetInstance()->getBitmap(IMG_PLAYER1)->getWidth() * m_iMultiple;
	m_iHeight = BitmapManager::GetInstance()->getBitmap(IMG_PLAYER1)->getHeight() * m_iMultiple;

	// 사람, 사자에 대한 충돌범위 저장
	m_RectList.clear();
	m_RectList.push_back(getLionRect());
	m_RectList.push_back(getPlayerRect());

	m_eState = PLAYER_STATE_IDLE;

	m_fMoveAnimTick = 0.0f;
	m_fJumpTick = 0.0f;
	m_dwPrevTime = GetTickCount();
	m_dwCurTime = GetTickCount();
}


Player::Player()
{
	m_aMoveAnimation[0] = IMG_PLAYER1;
	m_aMoveAnimation[1] = IMG_PLAYER2;
	m_aMoveAnimation[2] = IMG_PLAYER3;
	m_aWinAnimation[0] = IMG_PLAYER_WIN1;
	m_aWinAnimation[1] = IMG_PLAYER_WIN2;
}

Player::~Player()
{
}
