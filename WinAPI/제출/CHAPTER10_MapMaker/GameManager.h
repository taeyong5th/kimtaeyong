#pragma once
#include "GlobalDefine.h"
#include "Block.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
	void start();
	void init();
	void initResource(HWND hWnd);	
	void load();
	void save();
private:
	int m_iRowCount, m_iColCount;
	// 지뢰 찾기 맵 그려질 위치
	const int m_iTop = 43;
	const int m_iLeft = 43;
	HWND m_hWnd;
	Block* m_Map[MAP_WIDTH_MAX][MAP_HEIGHT_MAX];
	bool m_bClickable; // 연속 클릭 방지 타이머
	int m_iBlockWidth;
	int m_iBlockHeight;
		
	//타임체크용
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fClickTime;	

	bool isValidRange(int x, int y); // x, y 값이 Map 배열 범위 내인지 검사
};

