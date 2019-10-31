#include "ScoreData.h"
#include <fstream>
#include <string>

int ScoreData::loadScore(GAME_SCORE type)
{
	int score = 0;
	std::ifstream file;
	switch (type)
	{
	case AIRPLANE_BEST_SCORE:
		file.open("airplane_best_score.txt", std::ios_base::in);
		break;
	case CONFETTI_BEST_SCORE:
		file.open("confettie_best_score.txt", std::ios_base::in);
		break;
	default:
		break;
	}

	if (file.is_open())
	{
		file >> score;
	}
	file.close();

	return score;
}

bool ScoreData::saveScore(GAME_SCORE type, int score)
{
	std::ofstream file;
	switch (type)
	{
	case AIRPLANE_BEST_SCORE:
		file.open("airplane_best_score.txt", std::ios_base::out);
		break;
	case CONFETTI_BEST_SCORE:
		file.open("confettie_best_score.txt", std::ios_base::out);
		break;
	default:
		break;
	}
	// 파일 열기 실패
	if (!file.is_open()) return false;

	std::string str(std::to_string(score));
	file.write(str.c_str(), str.size());
	file.close();
	return true;
}

ScoreData::ScoreData()
{
}

ScoreData::~ScoreData()
{
}
