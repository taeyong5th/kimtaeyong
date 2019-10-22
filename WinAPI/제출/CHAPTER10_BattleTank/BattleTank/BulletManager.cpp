#include "BulletManager.h"
#include "TankManager.h"

void BulletManager::add(Bullet b)
{
	m_BulletList.push_back(b);
}

void BulletManager::update(Block* map[][MAP_HEIGHT], TankManager* enemyTanks)
{
	RECT mapRect;
	RECT rect;
	Tank tank;
	for (auto iter = m_BulletList.begin(); iter != m_BulletList.end();)
	{
		iter->update();
		mapRect = iter->m_MapRect;

		// 폭발 애니메이션 중이면 검사하지않음
		if (iter->getState() == MOVE_STATE_EXPLOSION)
		{
			++iter;
			continue;
		}

		// 블럭과 충돌하면 폭발
		for (int i = 0; i < MAP_WIDTH; i++)
		{
			for (int j = 0; j < MAP_HEIGHT; j++)
			{
				if (iter->isCollision(map[i][j]->getRect()))
				{
					map[i][j]->Attacked(iter->getState());
					iter->setState(MOVE_STATE_EXPLOSION);
				}
			}
		}

		// 적 탱크와 충돌하면 폭발
		if (enemyTanks != nullptr && enemyTanks->isCollision(iter->getRect()))
		{
			iter->setState(MOVE_STATE_EXPLOSION);
		}

		// 맵 범위 밖으로 나가면 die
		if (! iter->isCollision(mapRect))
		{
			iter->setState(MOVE_STATE_DIE);
		}

		// die 상태인 불릿은 제거한다.
		if (iter->getState() == MOVE_STATE_DIE)
		{
			iter = m_BulletList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void BulletManager::draw()
{
	for (auto iter = m_BulletList.begin(); iter != m_BulletList.end(); ++iter)
	{
		iter->draw();
	}
}

void BulletManager::clear()
{
	m_BulletList.clear();
}

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
}
