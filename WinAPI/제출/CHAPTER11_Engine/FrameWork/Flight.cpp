#include "Flight.h"
#include "ResoucesManager.h"

void Flight::init()
{
	m_pBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//FlightGameFlight.bmp");	
	m_pBitmap->SetAnchor(JEngine::ANCHOR_CENTER);
	m_pExplosion[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//explosion1.bmp");
	m_pExplosion[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//explosion2.bmp");
	m_pExplosion[2] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//explosion3.bmp");
	for (int i = 0; i < 3; ++i)
	{
		m_pExplosion[i]->SetAnchor(JEngine::ANCHOR_CENTER);
	}

	memset(&m_BodyRect, 0, sizeof(JEngine::RECT));
	memset(&m_WingRect, 0, sizeof(JEngine::RECT));

	m_bisDie = false;
	m_iExplosionAnimIndex = 0;
	m_fExplosionTime = 0.0f;
	m_iScore = 0;
}

void Flight::setPos(JEngine::POINT flighitPoint)
{
	JEngine::RECT rect;
	rect.top = 94;
	rect.bottom = 611;
	rect.left = 0;
	rect.right = 414;

	if (rect.isPtin(flighitPoint))
	{
		m_curPoint = flighitPoint;
	}
	
	m_BodyRect.left = m_curPoint.x - 5;
	m_BodyRect.right = m_curPoint.x + 5;
	m_BodyRect.top = m_curPoint.y - 30;
	m_BodyRect.bottom = m_curPoint.y + 30;

	m_WingRect.left = m_curPoint.x - 33;
	m_WingRect.right = m_curPoint.x + 33;
	m_WingRect.top = m_curPoint.y - 8;
	m_WingRect.bottom = m_curPoint.y + 8;
	
}

void Flight::update(float fETime)
{
	if (m_bisDie)
	{
		m_fExplosionTime += fETime;
		if (m_fExplosionTime >= m_fExplosionAnimTick)
		{
			m_iExplosionAnimIndex++;
			m_fExplosionTime = 0.0f;			
		}
		if (m_iExplosionAnimIndex > 2)
		{
			m_iExplosionAnimIndex = 0;
			m_bisDie = false;
		}
	}
}

void Flight::draw()
{
	if (m_bisDie)
	{
		m_pExplosion[m_iExplosionAnimIndex]->Draw(m_curPoint);
	}
	else
	{
		m_pBitmap->Draw(m_curPoint);
	}	
}

JEngine::POINT Flight::getPoint()
{
	return m_curPoint;
}

bool Flight::isCollision(JEngine::RECT rect)
{
	if (m_BodyRect.isCollision(rect) || m_WingRect.isCollision(rect))
	{
		return true;
	}
	return false;
}

bool Flight::isCollision(JEngine::POINTF rect)
{
	if (m_BodyRect.isPtin(rect) || m_WingRect.isPtin(rect))
	{
		return true;
	}
	return false;
}

void Flight::setDie(bool isDie)
{
	m_bisDie = isDie;
}

void Flight::addScore(int score)
{
	m_iScore += score;
}

int Flight::getScore()
{
	return m_iScore;
}


Flight::Flight()
{
}

Flight::~Flight()
{
}
