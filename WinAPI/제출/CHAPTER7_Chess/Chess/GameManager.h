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
	STATE_CHOOSE_POSITION,
	STATE_CHOOSE_PROMOTION
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
	void clickEvent(HWND hWnd, POINT point);
	void draw(HDC hdc);
	Piece* PromotePiece(Piece* pawn, PROMOTION_BUTTON btn); // pawn을 프로모션 시킨다.
	void nextTurn();
	GameManager(HWND hWnd);
	~GameManager();
};