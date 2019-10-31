#pragma once
#include "SingleTon.h"

enum GAME_SCORE 
{
	AIRPLANE_BEST_SCORE,
	CONFETTI_BEST_SCORE
};

class ScoreData : public SingleTon <ScoreData>
{
private:


public:
	int loadScore(GAME_SCORE type);
	bool saveScore(GAME_SCORE type, int score);
	ScoreData();
	~ScoreData();
};