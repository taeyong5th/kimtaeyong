#pragma once
#include <Windows.h>
#include "GameDefine.h"
#include "Button.h"
#include "Piece.h"

enum GAMEINFO_BUTTON
{
	GAMEINFO_BUTTON_NONE,
	GAMEINFO_BUTTON_RESET
};

class GameinfoUI
{
private:
	Button* m_btnTurn, * m_btnTeam;
	Button* m_btnReset;

public:
	GameinfoUI();
	~GameinfoUI();
	void update(TEAM team, UINT turnCount);	
	void draw(HDC hdc);
	GAMEINFO_BUTTON click(POINT point);
};