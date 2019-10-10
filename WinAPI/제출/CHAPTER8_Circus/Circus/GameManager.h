#pragma once
#include "GameDefine.h"
#include "Background.h"
#include "Player.h"
#include "FireCircle.h"
#include "Jar.h"
#include "Goal.h"

enum GAME_STATE
{
	GAME_PAUSE,
	GAME_PLAYING
};

class GameManager
{
private:
	GAME_STATE m_eState;
	HWND m_hWnd;
	int camera_x, player_x;
	Background m_bg;
	Player m_Player;
	Jar m_jar;
	Goal m_goal;
	FireCircle m_fire;
	int m_iHeart;

	//타임체크용
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fPauseTime;

public:
	void init(HWND hWnd);
	void update();
	GameManager();
	~GameManager();
};