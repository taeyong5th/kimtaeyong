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
	JEngine::POINT m_FirstClick; // 처음 마우스 누른 위치
	JEngine::POINT m_LastClick; // 마우스 뗀 위치
	int m_iPaperX, m_iPaperY;
	int m_iScore; // 총점
	int m_iScoreBonus; // 맞췄을때 추가될 점수
	int m_iPaperIdx;
	Paper m_aPapers[PAPER_COLOR_COUNT]; // 색종이 4장
	PAPER_COLOR m_eSelectedColor; // 현재 선택된 컬러

	GAME_STATE m_eState;
	
	float m_fPlayTime;
	const float m_fPlayLimitTime = 20.0f;
	float m_fGameOverTime;
	const float m_fGameOverLimitTime = 2.0f;
	
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
