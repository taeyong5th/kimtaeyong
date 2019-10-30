#include "Flight.h"
#include "ResoucesManager.h"

void Flight::init()
{
	m_pBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//FlightGameFlight.bmp");	
	m_pBitmap->SetAnchor(JEngine::ANCHOR_CENTER);
	memset(&m_BodyRect, 0, sizeof(JEngine::RECT));
	memset(&m_WingRect, 0, sizeof(JEngine::RECT));
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
}

void Flight::draw()
{
	m_pBitmap->Draw(m_curPoint);
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

Flight::Flight()
{
}

Flight::~Flight()
{
}
