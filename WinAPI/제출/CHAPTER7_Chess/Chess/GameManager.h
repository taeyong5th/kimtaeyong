#pragma once
#include <Windows.h>
#include <set>
#include "GameDefine.h"
#include "GameinfoUI.h"
#include "PromotionUI.h"
#include "BitmapManager.h"
#include "Board.h"

enum GAME_STATE
{
	STATE_CHOOSE_PIECE,
	STATE_CHOOSE_MOVE_POSITION,
	STATE_PROMOTION
};

class GameManager
{
private:
	UINT m_iTurnCount;
	TEAM m_eTurn;
	Board m_board;
	Piece* m_SelectedPiece;
	GAME_STATE m_eState;
	PromotionUI m_PromotionUI;
	GameinfoUI m_GameInfoUI;

public:
	void init();
	void start();
	void clickEvent(HWND hWnd, POINT point);
	void draw(HDC hdc);
	bool isChecked(TEAM team); // team의 킹이 체크된 상태인지
	void nextTurn();
	GameManager(HWND hWnd);
	~GameManager();
};