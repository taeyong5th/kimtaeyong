#pragma once
#include "GameDefine.h"
#include "Background.h"
#include "Player.h"
#include "FireCircle.h"
#include "Jar.h"
#include "Goal.h"
#include "IntroUI.h"

enum GAME_STATE
{
	GAME_INTRO,
	GAME_PLAYING,
	GAME_OVER
};

class GameManager
{
private:
	GAME_STATE m_eState;
	HWND m_hWnd;
	int camera_x, player_x;
	Background m_bg;
	Player m_Player;
	Goal m_goal;
	FireCircle m_fires[2];
	Jar m_jars[3]; // 
	int m_iHeart;
	
	//타임체크용
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fPauseTime;

	void updateObjects(std::vector<CircusObject*> objects);
	void drawObjects(std::vector<CircusObject*> objects);
	void intro();
	void play();
public:
	void init(HWND hWnd);
	void update();
	GameManager();
	~GameManager();
};