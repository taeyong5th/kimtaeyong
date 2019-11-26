#pragma once
#include "JEngine.h"
#include "defines.h"

class TitleScene : public JEngine::Scene
{
private:

	// 핸들정보
	HWND m_hWnd;
		
	OMOK_PLAYER_ID m_PlayerID;

	// 바둑돌 정보
	JEngine::BitMap*	m_pStone[2];	

	// 마우스의 현재 위치
	JEngine::POINT m_iMousePos;

	// 블럭 하나의 정보
	int m_iBlockWidth, m_iBlockHeight;
	JEngine::BitMap*	m_pBlock;

	// 오목판의 정보	
	int m_aBoard[BOARD_WIDTH][BOARD_HEIGHT];
	JEngine::RECT m_boardRect;

	std::function<bool()> clickEvent;

public:
	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();
	bool OnClick();

	void showMessage(string caption, string text);
	TitleScene();
	virtual ~TitleScene();
};

