#include "Bullet.h"
#include "ResoucesManager.h"
#include "Label.h"


void Bullet::init(JEngine::POINT flighitPoint)
{
	m_pBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//FlightGameBullet.bmp");
	m_pBitmap->SetAnchor(JEngine::ANCHOR_CENTER);
	
	// ����� ������ġ
	m_FlightPoint = flighitPoint;

	// �Ҹ��� ������ ������ġ ���
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
	
	// x, y ���� ����
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

	// �Ҹ��� ���ư� ���� ���
	if ((m_curPoint.x - m_FlightPoint.x) != 0)
	{
		theta = abs(atanf(((float)m_curPoint.y - (float)m_FlightPoint.y) / ((float)m_curPoint.x - (float)m_FlightPoint.x)));
	}
}

void Bullet::draw()
{
	m_pBitmap->Draw(m_curPoint.x, m_curPoint.y);
	//JEngine::Label label;
	//label.Init(to_string((int)m_curPoint.x) + ", " + to_string((int)m_curPoint.y), m_curPoint.x, m_curPoint.y, 0);
	//label.Draw();
}

void Bullet::update(float fETime)
{
	if ((m_curPoint.x - m_FlightPoint.x) != 0)
	{
		m_curPoint.x += fETime * m_BulletSpeed * cosf(theta) * m_ixDirection;
		m_curPoint.y += fETime * m_BulletSpeed * sinf(theta) * m_iyDirection;
	}
	else
	{
		m_curPoint.y += fETime * m_BulletSpeed * sinf(theta) * m_iyDirection;
	}

}

JEngine::POINTF Bullet::getPoint()
{
	return m_curPoint;
}

bool Bullet::isInside()
{
	JEngine::RECT rect;
	rect.top = 94;
	rect.bottom = 611;
	rect.left = 0;
	rect.right = 414;

	return rect.isPtin(m_curPoint);
}

Bullet::Bullet()
{
	m_pBitmap = nullptr;
	memset(&m_curPoint, 0, sizeof(JEngine::POINT));
}

Bullet::~Bullet()
{
}
