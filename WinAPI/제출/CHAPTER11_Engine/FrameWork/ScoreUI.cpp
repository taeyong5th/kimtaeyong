#include "ScoreUI.h"

ScoreUI::ScoreUI()
{

}

ScoreUI::~ScoreUI()
{
}

void ScoreUI::init()
{	
	m_strScore = "0";
}

void ScoreUI::update(float fEtime, int score)
{
	m_strScore = to_string(score);

	int size = m_strScore.size();
	int pos = size % 3;

	while (pos < size && size > 3)
	{
		m_strScore.insert(pos, ",");
		size = m_strScore.size();
		pos += 4;
	}
}

void ScoreUI::draw(int x, int y)
{
	m_ScoreLabel.Init(m_strScore, x, y, 0);
	m_ScoreLabel.Draw();
}
