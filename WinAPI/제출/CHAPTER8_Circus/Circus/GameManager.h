#pragma once
#include "GameDefine.h"
#include "Background.h"
#include "Player.h"

class GameManager
{
private:
	HWND m_hWnd;
	int camera_x;
	Background m_bg;
	Player m_Player;

public:
	void init(HWND hWnd);
	void update();
	GameManager();
	~GameManager();
};