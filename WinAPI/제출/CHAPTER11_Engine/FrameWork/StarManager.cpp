#include "StarManager.h"
#include "Flight.h"
#include "Label.h"

void StarManager::init()
{
	m_Stars.clear();
	m_iScore = 100;
}

void StarManager::createBullet(JEngine::POINT flighitPoint)
{
	Star* star = new Star;
	star->init(flighitPoint);
	m_Stars.push_back(star);
}

void StarManager::draw()
{
	for (auto iter = m_Stars.begin(); iter != m_Stars.end(); ++iter)
	{
		(*iter)->draw();
		JEngine::Label label;
		label.Init(to_string(m_iScore), (*iter)->getPoint().x - 10, (*iter)->getPoint().y - 5, 0);
		label.Draw();
	}
}

void StarManager::update(float fETime, Flight& flight)
{
	for (auto iter = m_Stars.begin(); iter != m_Stars.end(); )
	{
		(*iter)->update(fETime);

		// 비행기와 충돌하면 제거
		if (flight.isCollision((*iter)->getRECT()))
		{
			m_iScore += 100;
			iter = m_Stars.erase(iter);
		}
		// 외부로 나가면 제거
		else if (!(*iter)->isInside())
		{
			iter = m_Stars.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

StarManager::StarManager()
{
}

StarManager::~StarManager()
{
}
