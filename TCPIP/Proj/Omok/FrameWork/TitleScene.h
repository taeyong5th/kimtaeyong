#pragma once
#include "JEngine.h"
#include "defines.h"

class TitleScene : public JEngine::Scene
{
private:

	// �ڵ�����
	HWND m_hWnd;
		
	OMOK_PLAYER_ID m_PlayerID;

	// �ٵϵ� ����
	JEngine::BitMap*	m_pStone[2];	

	// ���콺�� ���� ��ġ
	JEngine::POINT m_iMousePos;

	// �� �ϳ��� ����
	int m_iBlockWidth, m_iBlockHeight;
	JEngine::BitMap*	m_pBlock;

	// �������� ����	
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

