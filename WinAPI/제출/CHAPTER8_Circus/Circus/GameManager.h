#pragma once
#include "GameDefine.h"
#include "Background.h"
#include "Player.h"
#include "FireCircle.h"
#include "Jar.h"
#include "Goal.h"
#include "Meter.h"
#include "IntroUI.h"
#include "ScoreUI.h"

enum GAME_STATE
{
	GAME_INTRO,
	GAME_PLAY,
	GAME_CLEAR,
	GAME_OVER
};

class GameManager
{
private:
	GAME_STATE m_eState;
	HWND m_hWnd;
	int m_iCameraX, m_iPlayerX;
	Background m_bg;
	Player m_Player;
	Goal m_goal;
	FireCircle m_fires[2];
	Jar* m_jars; // 
	Meter* m_Meters;
	int m_eJarCount;
	int m_iMapWidth;

	// 점수 관련
	int m_iScore;
	int m_iBestScore;
	int m_iHeart;

	// UI
	IntroUI m_IntroUI;
	ScoreUI m_ScoreUI;
	
	//타임체크용
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fPauseTime;

	void gameIntro();
	void gameInit();
	void gamePlay();
	void gameOver();
	void gameClear();
	void draw();	
public:
	void initResource(HWND hWnd);
	void update();
	GameManager();
	~GameManager();
};