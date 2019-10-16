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
	// ���� ã�� �� �׷��� ��ġ
	const int m_iTop = 43; 
	const int m_iLeft = 45; 
	HWND m_hWnd;
	//MapDraw m_Mapdraw;
	Element* m_Map[MAP_WIDTH_MAX][MAP_HEIGHT_MAX];	
	int m_iMineCount;
	int m_iMineMax;
	
	//Ÿ��üũ��
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fGameTime;

	int countMine(int i, int j); // m_Map[i][j] �ֺ��� ���� ������ ��ȯ�Ѵ�.
	void openMine(int i, int j); // m_Map[i][j] ��ġ�� open�Ѵ�.
	bool isWin(); // �¸����� üũ�Ѵ�.
	bool isValidRange(int x, int y); // x, y ���� Map �迭 ���� ������ �˻�
};

