#pragma once
#include "GameDefine.h"
#include "Background.h"
#include "Player.h"
#include "FireCircle.h"
#include "Jar.h"
#include "Goal.h"

class GameManager
{
private:
	HWND m_hWnd;
	int camera_x;
	Background m_bg;
	Player m_Player;
	Jar m_jar;

public:
	void init(HWND hWnd);
	void update();
	GameManager();
	~GameManager();
};