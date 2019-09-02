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
	Point m_characterPos; // ĳ���� ��ġ
	Point m_GoalPos; // ��ǥ ��ġ
	//list<Point>::iterator m_characterIter;
	//list<Point>::iterator m_GoalIter;

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