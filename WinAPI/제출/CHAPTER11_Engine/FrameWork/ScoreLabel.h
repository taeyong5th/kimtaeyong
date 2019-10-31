#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "SingleTon.h"

class ScoreUI : public SingleTon<ScoreUI>
{
private:

public:
	ScoreUI();
	~ScoreUI();
	void init();
	void update(float fEtime);
	void draw();
	void addFever(int score = 1);
	bool isFeverMode();
};