#pragma once
#include <Windows.h>
#include <filesystem>
#include "GameDefine.h"
#include "BitmapManager.h"
#include "Board.h"

class GameManager
{
private:
	Board m_board;

public:
	void init();
	void start();
	void draw(HDC hdc);
	GameManager(HWND hWnd);
	~GameManager();
};