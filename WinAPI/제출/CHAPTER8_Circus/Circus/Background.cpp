#include "Background.h"

void Background::init(int x, int y)
{
	m_ix = x;
	m_iy = y;
	m_eAnim = BG_ANIM_STOP;
}

void Background::update(int x, int y)
{
	m_ix = -x;
	m_iy = -y;
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;
	m_fAnimTick += m_fDeltaTime;
	if (m_fAnimTick > 0.1f) // 0.1초마다 그릴 이미지 변경
	{
		m_fAnimTick = 0.0f;
		m_iAnimCount = ++m_iAnimCount % 2;
	}
	// 애니메이션을 멈춘 상태면 0번째 이미지로만 보여지게함
	if (m_eAnim == BG_ANIM_STOP)
	{
		m_iAnimCount = 0;
	}	
}

void Background::draw()
{
	// 배경 그리기
	int bitmapWidth; // 각 비트맵(원본)의 가로 길이
	int tempX = m_ix; // 코끼리와 관중이 그려질 위치를 저장할 변수
	for (int i = 0; tempX < WINDOW_WIDTH; i++)
	{
		// 6번째마다 코끼리를 그린다.
		if (i % 6 == 5)
		{
			bitmapWidth = BitmapManager::GetInstance()->getBitmap(IMG_BG_ELEPHANT)->getWidth();
			BitmapManager::GetInstance()->prepare(IMG_BG_ELEPHANT, tempX, m_iy, m_iMultiple, m_iMultiple);
			tempX += bitmapWidth * m_iMultiple;
		}
		else
		{
			bitmapWidth = BitmapManager::GetInstance()->getBitmap(m_aAnimation[m_iAnimCount])->getWidth();
			BitmapManager::GetInstance()->prepare(m_aAnimation[m_iAnimCount], tempX, m_iy + 3 * m_iMultiple, m_iMultiple, m_iMultiple);
			tempX += bitmapWidth * m_iMultiple;
		}

		// 초록색 잔디 그리기
		bitmapWidth = BitmapManager::GetInstance()->getBitmap(IMG_BG_GROUND)->getWidth();
		BitmapManager::GetInstance()->prepare(IMG_BG_GROUND, m_ix + (bitmapWidth * m_iMultiple * i), m_iy + 67 * m_iMultiple, m_iMultiple, m_iMultiple);
	}
}

void Background::setAnimState(BG_ANIM anim)
{
	m_eAnim = anim;
}

Background::Background()
{

	m_dwPrevTime = GetTickCount();
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = 0.0f;
	m_fAnimTick = 0.0f;
	m_iAnimCount = 0;

	m_aAnimation[0] = IMG_BG_CROWD;
	m_aAnimation[1] = IMG_BG_CROWD2;

}

Background::~Background()
{
}
