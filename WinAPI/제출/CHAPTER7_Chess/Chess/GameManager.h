#pragma once
#include <Windows.h>
#include <filesystem>
#include "GameDefine.h"
#include "PromotionUI.h"
#include "BitmapManager.h"
#include "Board.h"

enum GAME_STATE
{
	STATE_START,
	STATE_PLAY,
	STATE_PROMOTION,
};

class GameManager
{
private:
	TEAM m_eTurn;
	Board m_board;
	Piece* m_SelectedPiece;
	GAME_STATE m_eState;
	PromotionUI m_PromotionUI;

public:
	void init();
	void start();	
	void clickEvent(HWND hWnd, POINT point);
	void draw(HDC hdc);
	GameManager(HWND hWnd);
	~GameManager();
};