#include "StarManager.h"
#include "Flight.h"
#include "Label.h"
#include "FeverMode.h"
#include "ScoreUI.h"

void StarManager::init()
{
	for (auto iter = m_Stars.begin(); iter != m_Stars.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	m_Stars.clear();
	m_iScore = 100;
}

void StarManager::createStar(JEngine::POINT flighitPoint)
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
		string strScore = to_string(m_iScore);
		label.Init(strScore, (*iter)->getPoint().x - (strScore.size() << 2), (*iter)->getPoint().y - 5, 0);
		label.Draw();
	}
}

void StarManager::update(float fETime, Flight& flight)
{
	for (auto iter = m_Stars.begin(); iter != m_Stars.end(); )
	{
		(*iter)->update(fETime);

		// �浹�ϸ� ���� ����
		if (flight.isCollision((*iter)->getRECT()))
		{
			flight.addScore(m_iScore);
			ScoreUI::GetInstance()->update(fETime, flight.getScore());
			FeverMode::GetInstance()->addFever(2);
			m_iScore += 100;
			SAFE_DELETE(*iter);
			iter = m_Stars.erase(iter);			
		}
		// �ܺη� ������ ����
		else if (!(*iter)->isInside())
		{
			SAFE_DELETE(*iter);
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
	for (auto iter = m_Stars.begin(); iter != m_Stars.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	m_Stars.clear();
}
