#pragma once
#include "Mecro.h"
#include "MapDraw.h"
#include "GameDefine.h"
#include "Point.h"
#include <vector>

class GameManager
{
private:
	MapDraw m_MapDraw;
	vector<PointType> m_MapDataList[MAP_SIZE_HEIGHT];
	Point m_characterPos; // ĳ���� ��ġ
	Point m_GoalPos; // ��ǥ ��ġ

	void printMap(); // ���� ���
	void printCharacter(); // ĳ���͸� ���
	void moveCharacter(int key); // ĳ���͸� �̵�
	bool isClear(); // ���� Ŭ���� ���� ����


public:
	void init();
	void start();
	GameManager();
	~GameManager();

};