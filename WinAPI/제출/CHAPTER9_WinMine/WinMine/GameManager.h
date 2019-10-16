#pragma once
#include "GlobalDefine.h"
#include "Element.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
	void start();
	void init(int rowCount, int colCount);
	void initResource(HWND hWnd);	
private:
	int m_iRowCount, m_iColCount;
	// 지뢰 찾기 맵 그려질 위치
	const int m_iTop = 43; 
	const int m_iLeft = 45; 
	HWND m_hWnd;
	//MapDraw m_Mapdraw;
	Element* m_Map[MAP_WIDTH_MAX][MAP_HEIGHT_MAX];	
	int m_iMineCount;
	int m_iMineMax;
	
	//타임체크용
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fGameTime;

	int countMine(int i, int j); // m_Map[i][j] 주변의 지뢰 개수를 반환한다.
	void openMine(int i, int j); // m_Map[i][j] 위치를 open한다.
	bool isWin(); // 승리여부 체크한다.
	bool isValidRange(int x, int y); // x, y 값이 Map 배열 범위 내인지 검사
};

