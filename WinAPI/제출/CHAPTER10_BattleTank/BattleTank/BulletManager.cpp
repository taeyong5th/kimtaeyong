#include "BulletManager.h"

void BulletManager::add(Bullet b)
{
	m_BulletList.push_back(b);
}

void BulletManager::update(Block* map[][MAP_HEIGHT])
{
	RECT mapRect;
	RECT bulletRect;
	RECT rect;
	for (auto iter = m_BulletList.begin(); iter != m_BulletList.end();)
	{
		iter->update();
		mapRect = iter->m_MapRect;
		bulletRect = iter->getRect();


		// ���� �浹�ϸ� ����
		for (int i = 0; i < MAP_WIDTH; i++)
		{
			for (int j = 0; j < MAP_HEIGHT; j++)
			{
				if (IntersectRect(&rect, &map[i][j]->getRect(), &bulletRect))
				{
					map[i][j]->Attacked(iter->getState());
					iter->setState(MOVE_STATE_EXPLOSION);					
				}
			}
		}

		// �� ���� ������ ������ die
		if (!IntersectRect(&rect, &mapRect, &bulletRect))
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
