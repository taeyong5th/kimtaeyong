#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "SingleTon.h"
#include "Label.h"

class ScoreUI : public SingleTon<ScoreUI>
{
private:
	JEngine::Label m_ScoreLabel;
	string m_strScore;
public:
	ScoreUI();
	~ScoreUI();
	void init();
	void update(float fEtime, int score);
	void draw(int x, int y);
};