#include "BulletManager.h"
#include "StarManager.h"
#include "Flight.h"
#include "FeverMode.h"

void BulletManager::init()
{
	for (auto iter = m_Bullets.begin(); iter != m_Bullets.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
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
			flight.setDie(true);
			m_Bullets.clear();
			StarManager::GetInstance()->init();
			FeverMode::GetInstance()->init();
			break;
		}

		// 불릿이 외부로 나가면 제거
		if (!(*iter)->isInside())
		{
			SAFE_DELETE(*iter);
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
	for (auto iter = m_Bullets.begin(); iter != m_Bullets.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	m_Bullets.clear();
}
