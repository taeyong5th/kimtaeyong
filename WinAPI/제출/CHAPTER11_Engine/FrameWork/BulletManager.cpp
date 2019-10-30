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
		
		// ������ �浹�ϴ��� �˻�
		if (flight.isCollision((*iter)->getPoint()))
		{
			m_Bullets.clear();
			break;
		}

		// �Ҹ��� �ܺη� ������ ����
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
