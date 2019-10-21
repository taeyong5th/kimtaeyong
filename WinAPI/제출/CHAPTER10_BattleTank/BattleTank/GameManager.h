#pragma once
#include "GlobalDefine.h"
#include "Block.h"
#include "Player.h"
#include "Bullet.h"

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
	void initGame();
	void initResource(HWND hWnd);	
	void loadStage();
	void update();

private:
	int m_iRowCount, m_iColCount;
	// �� �׷��� ��ġ
	RECT m_MapRect;
	HWND m_hWnd;
	Block* m_Map[MAP_WIDTH][MAP_HEIGHT];
	Player m_Player;
	Player m_Enemies[6];
	int m_iBlockWidth;
	int m_iBlockHeight;

	int m_iPlayerX, m_iPlayerY;
	int m_iStage; // ���� ��������
	int m_iEnemyCount; // ���� �������
		
	//Ÿ��üũ��
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fEnemyGenTime;

	void gameIntro();
	void gamePlay();
	void gameOver();
	void gameClear();
	void draw();
	bool isValidRange(int x, int y); // x, y ���� Map �迭 ���� ������ �˻�
};

