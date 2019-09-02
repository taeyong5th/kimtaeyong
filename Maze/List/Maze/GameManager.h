#pragma once
#include "Mecro.h"
#include "MapDraw.h"
#include "GameDefine.h"
#include "Point.h"
#include <List>

class GameManager
{
private:
	MapDraw m_MapDraw;
	list<Point> m_MapDataList;
	Point m_characterPos; // 캐릭터 위치
	Point m_GoalPos; // 목표 위치
	//list<Point>::iterator m_characterIter;
	//list<Point>::iterator m_GoalIter;

	void printMap(); // 맵을 출력
	void printCharacter(); // 캐릭터를 출력
	void moveCharacter(int key); // 캐릭터를 이동
	bool isClear(); // 게임 클리어 여부 조사


public:
	void init();
	void start();
	GameManager();
	~GameManager();

};