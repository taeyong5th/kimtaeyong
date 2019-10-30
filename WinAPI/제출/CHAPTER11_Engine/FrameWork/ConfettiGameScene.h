#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "Paper.h"
#include "defines.h"



class ConfettiGameScene : public JEngine::Scene
{
private:
	JEngine::BitMap* m_pBack;
	JEngine::BitMap* m_pTimeBar;
	JEngine::BitMap* m_pTimeOver;
	JEngine::BitMap* m_pFeverEffect;
	JEngine::BitMap* m_pFeverBack;
	JEngine::BitMap* m_pFeverBar1;
	JEngine::BitMap* m_pFeverBar2;
	JEngine::BitMap* m_pFeverBar3;
	JEngine::POINT m_FirstClick;
	JEngine::POINT m_LastClick;
	int x, y;
	int m_iScore;
	int m_iFeverScore;
	const int m_iFeverScoreMax = 1000;
	int m_iPaperIdx;
	Paper m_aPapers[PAPER_COLOR_COUNT];
	PAPER_COLOR m_eSelectedColor;

	GAME_STATE m_eState;

	float m_fFeverAnimTime;

	float m_fPlayTime;
	const float m_fPlayLimitTime = 15.0f;
	float m_fFeverTime;
	const float m_fFeverLimitTime = 5.0f;
	float m_fGameOverTime;
	const float m_fGameOverLimitTime = 2.0f;
	bool m_bFeverDraw;
	bool m_bFeverMode;

	std::function<bool()> clickEvent;

public:
	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();
	bool OnClick();

	ConfettiGameScene();
	virtual ~ConfettiGameScene();
};
