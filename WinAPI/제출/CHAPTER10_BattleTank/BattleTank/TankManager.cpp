#include "TankManager.h"

void TankManager::add(Tank b)
{
	m_TankList.push_back(b);
}

void TankManager::update(Block* map[][MAP_HEIGHT], TankManager* enemyTanks)
{
	for (auto iter = m_TankList.begin(); iter != m_TankList.end(); ++iter)
	{
		iter->update(map, enemyTanks);
	}
}

void TankManager::draw()
{
	for (auto iter = m_TankList.begin(); iter != m_TankList.end(); ++iter)
	{
		iter->draw();
	}
}

void TankManager::clear()
{
	m_TankList.clear();
}

int TankManager::size()
{
	return m_TankList.size();
}

bool TankManager::isCollision(RECT bulletRect)
{
	for (auto iter = m_TankList.begin(); iter != m_TankList.end(); ++iter)
	{
		// rect와 충돌하면 체력을 깎고 체력이 0이면 제거한다.
		if (iter->isCollision(bulletRect))
		{
			iter->setHP(iter->getHP() - 1);
			if(iter->getHP() == 0)
				m_TankList.erase(iter);
			return true;
		}
	}
	return false;
}

void TankManager::setState(MOVE_STATE state)
{
	for (auto iter = m_TankList.begin(); iter != m_TankList.end(); ++iter)
	{
		iter->setState(state);
	}
}

void TankManager::shootBullet()
{
	for (auto iter = m_TankList.begin(); iter != m_TankList.end(); ++iter)
	{
		iter->shootBullet();
	}
}

std::list<Tank>::iterator TankManager::begin()
{
	return m_TankList.begin();
}

TankManager::TankManager()
{

}

TankManager::~TankManager()
{
	m_TankList.clear();
}
