#pragma once
#include "GlobalDefine.h"
#include "Element.h"

struct Cursor
{
	int x;
	int y;
	std::string shape; // Ŀ���� ���
};

class GameManager
{
public:
	GameManager();
	~GameManager();
	void start();
private:
	//MapDraw m_Mapdraw;
	Element* m_Map[WIDTH][HEIGHT];
	Cursor m_Cursor;
	int m_iMineCount;

	void adjustCursorPosition(); // Ŀ�� ��ġ�� ���� ������ ������ �����Ѵ�.
	int countMine(int i, int j); // m_Map[i][j] �ֺ��� ���� ������ ��ȯ�Ѵ�.
	void openMine(int i, int j); // m_Map[i][j] ��ġ�� open�Ѵ�.
	bool isWin(); // �¸����� üũ�Ѵ�.
};

