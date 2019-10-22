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

		// ���� �ִϸ��̼� ���̸� �˻���������
		if (iter->getState() == MOVE_STATE_EXPLOSION)
		{
			++iter;
			continue;
		}

		// ���� �浹�ϸ� ����
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

		// �� ��ũ�� �浹�ϸ� ����
		if (enemyTanks != nullptr && enemyTanks->isCollision(iter->getRect()))
		{
			iter->setState(MOVE_STATE_EXPLOSION);
		}

		// �� ���� ������ ������ die
		if (! iter->isCollision(mapRect))
		{
			iter->setState(MOVE_STATE_DIE);
		}

		// die ������ �Ҹ��� �����Ѵ�.
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
