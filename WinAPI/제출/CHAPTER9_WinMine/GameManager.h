#pragma once
#include "GlobalDefine.h"
#include "Block.h"

enum GAME_LEVEL
{
	GAME_LEVEL_EASY,
	GAME_LEVEL_NORMAL,
	GAME_LEVEL_HARD,
	GAME_LEVEL_USER,
	GAME_LEVEL_AUTO
};

enum GAME_STATE
{
	GAME_PLAY,
	GAME_OVER
};

class GameManager
{
public:
	GameManager();
	~GameManager();
	void start();
	void init(GAME_LEVEL gameLevel = GAME_LEVEL_AUTO, int row = 0, int col = 0, int mineCount = 0);
	void initResource(HWND hWnd);	
private:
	int m_iRowCount, m_iColCount;
	// 지뢰 찾기 맵 그려질 위치
	const int m_iTop = 43;
	const int m_iLeft = 43;
	HWND m_hWnd;
	Block* m_Map[MAP_WIDTH_MAX][MAP_HEIGHT_MAX];
	int m_iMineCount;
	int m_iMineMax; 
	bool m_bClickable; // 연속 클릭 방지 타이머

	GAME_LEVEL m_eGameLevel;
	GAME_STATE m_eGameState;
	
	//타임체크용
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fGameTime;
	float m_fClickTime;	

	int countMine(int i, int j); // m_Map[i][j] 주변의 지뢰 개수를 반환한다.
	void openMine(int i, int j); // m_Map[i][j] 위치를 open한다.
	bool isWin(); // 승리여부 체크한다.
	bool isValidRange(int x, int y); // x, y 값이 Map 배열 범위 내인지 검사
};

