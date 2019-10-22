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
	void initGame(); // �������� �Ѿ������ �ʱ�ȭ �ؾߵǴ� �͵�
	void initResource(HWND hWnd);	
	void loadStage(int stageNum);
	void update();

private:
	HWND m_hWnd;

	// �� ����
	int m_iRowCount, m_iColCount; // �� ����, ���� ����
	int m_iBlockWidth, m_iBlockHeight; // �� 1���� ���� ,���� ũ��
	RECT m_MapRect;
	Block* m_Map[MAP_WIDTH][MAP_HEIGHT];
	Item m_item;
	
	// ��ũ ����
	TankManager m_PlayerTank;
	TankManager m_EnemyTanks;
	int m_iEnemyCreaetedCount; // �� ���� Ƚ��
	
	int m_iStageNum; // ���� ��������
	int m_iPlayerHP; // �÷��̾� ü��
		
	//Ÿ��üũ��
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
	bool isValidRange(int x, int y); // x, y ���� Map �迭 ���� ������ �˻�
};

