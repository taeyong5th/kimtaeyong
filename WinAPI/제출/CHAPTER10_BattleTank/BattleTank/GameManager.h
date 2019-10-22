#pragma once
#include "GlobalDefine.h"
#include "Block.h"
#include "TankManager.h"
#include "Bullet.h"
#include "Item.h"

enum GAME_STATE
{
	GAME_INTRO,
	GAME_PLAY,
	GAME_CLEAR,
	GAME_OVER
};

class GameManager
{
public:
	GAME_STATE m_eState;
	GameManager();
	~GameManager();
	void initGame(); // 스테이지 넘어갈때마다 초기화 해야되는 것들
	void initResource(HWND hWnd);	
	void loadStage(int stageNum);
	void update();

private:
	HWND m_hWnd;

	// 맵 관련
	int m_iRowCount, m_iColCount; // 블럭 가로, 세로 개수
	int m_iBlockWidth, m_iBlockHeight; // 블럭 1개당 가로 ,세로 크기
	RECT m_MapRect;
	Block* m_Map[MAP_WIDTH][MAP_HEIGHT];
	Item m_item;
	
	// 탱크 관련
	TankManager m_PlayerTank;
	TankManager m_EnemyTanks;
	int m_iEnemyCreaetedCount; // 적 생성 횟수
	
	int m_iStageNum; // 현재 스테이지
	int m_iPlayerHP; // 플레이어 체력
		
	//타임체크용
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fEnemyGenTime;
	float m_fItemGenTime; 
	float m_fPauseTime;	
	int m_iClearAnimCount;

	void gameIntro();
	void gamePlay();
	void gameOver();
	void gameClear();
	void draw();

	void addEnemy();
	void generateItem();
	bool isValidRange(int x, int y); // x, y 값이 Map 배열 범위 내인지 검사
};

