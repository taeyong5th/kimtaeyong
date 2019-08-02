#pragma once
#include "Mecro.h"
#include "MapDraw.h"
#include "Element.h"

struct Cursor
{
	int x;
	int y;
	string shape; // 커서의 모양
};

class GameManager
{
public:
	GameManager();
	~GameManager();
	void start();
private:
	MapDraw m_Mapdraw;
	Element* m_Map[WIDTH][HEIGHT];
	Cursor m_Cursor;
	int m_iMineCount;

	void adjustCursorPosition(); // 커서 위치가 범위 밖으로 나가면 보정한다.
	int countAround(int i, int j); // m_Map[i][j] 주변의 지뢰 개수를 반환한다.
	void openMine(int i, int j); // m_Map[i][j] 위치를 open한다.
	bool isWin(); // 승리여부 체크한다.
	void printPlayInfo(); // 플레이 정보를 출력한다.
};

