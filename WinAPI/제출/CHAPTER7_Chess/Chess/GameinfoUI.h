#pragma once
#include <Windows.h>
#include "GameDefine.h"
#include "Button.h"

class GameinfoUI
{
private:
	Button* m_btnTurn, * m_btnTeam;

public:
	GameinfoUI();
	~GameinfoUI();
	void draw(HDC hdc, TEAM team, UINT turnCount);
};