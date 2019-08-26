#pragma once
#include "Mecro.h"
#include "MapDraw.h"
#include "GameDefine.h"
#include "DBLinkedList.h"

class GameManager
{
private:
	MapDraw m_MapDraw;
	List m_MapDataList;
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