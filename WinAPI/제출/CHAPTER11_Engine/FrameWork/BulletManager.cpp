#include "BulletManager.h"
#include "Flight.h"

void BulletManager::init()
{
	m_Bullets.clear();
}

void BulletManager::createBullet(JEngine::POINT flighitPoint)
{
	Bullet* bullet = new Bullet;
	bullet->init(flighitPoint);
	m_Bullets.push_back(bullet);
}

void BulletManager::draw()
{
	for (auto iter = m_Bullets.begin(); iter != m_Bullets.end(); ++iter)
	{
		(*iter)->draw();
	}
}

void BulletManager::update(float fETime, Flight& flight)
{
	for (auto iter = m_Bullets.begin(); iter != m_Bullets.end(); )
	{
		(*iter)->update(fETime);
		
		// 비행기와 충돌하는지 검사
		if (flight.isCollision((*iter)->getPoint()))
		{
			m_Bullets.clear();
			break;
		}

		// 불릿이 외부로 나가면 제거
		if (!(*iter)->isInside())
		{
			iter = m_Bullets.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
}
