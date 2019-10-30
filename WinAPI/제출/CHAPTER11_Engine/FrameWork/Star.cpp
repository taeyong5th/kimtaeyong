#include "Star.h"
#include "ResoucesManager.h"
#include "Label.h"


void Star::init(JEngine::POINT flighitPoint)
{
	m_pBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//FlightGameStar.bmp");
	m_pBitmap->SetAnchor(JEngine::ANCHOR_CENTER);

	// 비행기 현재위치
	m_FlightPoint = flighitPoint;

	// 불릿이 생성될 랜덤위치 계산
	switch (rand() % 4)
	{
	case 0:
		m_curPoint.x = rand() % 380 + 20;
		m_curPoint.y = 95;
		break;
	case 1:
		m_curPoint.x = rand() % 380 + 20;
		m_curPoint.y = 610;
		break;
	case 2:
		m_curPoint.x = 1;
		m_curPoint.y = rand() % 470 + 110;
		break;
	case 3:
		m_curPoint.x = 413;
		m_curPoint.y = rand() % 470 + 110;
		break;
	}

	// x, y 방향 결정
	m_ixDirection = m_iyDirection = 1;
	if (m_FlightPoint.x > m_curPoint.x)
	{
		m_ixDirection = 1;
	}
	else
	{
		m_ixDirection = -1;
	}
	if (m_FlightPoint.y > m_curPoint.y)
	{
		m_iyDirection = 1;
	}
	else
	{
		m_iyDirection = -1;
	}

	// 불릿이 날아갈 각도 계산
	if ((m_curPoint.x - m_FlightPoint.x) != 0)
	{
		theta = abs(atanf(((float)m_curPoint.y - (float)m_FlightPoint.y) / ((float)m_curPoint.x - (float)m_FlightPoint.x)));
	}
}

void Star::draw()
{
	m_pBitmap->Draw(m_curPoint.x, m_curPoint.y);
	//JEngine::Label label;
	//label.Init(to_string((int)m_curPoint.x) + ", " + to_string((int)m_curPoint.y), m_curPoint.x, m_curPoint.y, 0);
	//label.Draw();
}

void Star::update(float fETime)
{
	if ((m_curPoint.x - m_FlightPoint.x) != 0)
	{
		m_curPoint.x += fETime * m_StarSpeed * cosf(theta) * m_ixDirection;
		m_curPoint.y += fETime * m_StarSpeed * sinf(theta) * m_iyDirection;
	}
	else
	{
		m_curPoint.y += fETime * m_StarSpeed * sinf(theta) * m_iyDirection;
	}

}

JEngine::POINTF Star::getPoint()
{
	return m_curPoint;
}

JEngine::RECT Star::getRECT()
{
	JEngine::RECT rect;
	rect.top = m_curPoint.y - m_pBitmap->GetHeight() / 2;
	rect.bottom = m_curPoint.y + m_pBitmap->GetHeight() / 2;
	rect.left = m_curPoint.x - m_pBitmap->GetWidth() / 2;
	rect.right = m_curPoint.x + m_pBitmap->GetWidth() / 2;
	
	return rect;
}

bool Star::isInside()
{
	JEngine::RECT rect;
	rect.top = 94;
	rect.bottom = 611;
	rect.left = 0;
	rect.right = 414;

	return rect.isPtin(m_curPoint);
}

Star::Star()
{
	m_pBitmap = nullptr;
	memset(&m_curPoint, 0, sizeof(JEngine::POINT));
}

Star::~Star()
{
}
