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
	JEngine::POINT m_FirstClick; // ó�� ���콺 ���� ��ġ
	JEngine::POINT m_LastClick; // ���콺 �� ��ġ
	int m_iPaperX, m_iPaperY;
	int m_iScore; // ����
	int m_iScoreBonus; // �������� �߰��� ����
	int m_iPaperIdx;
	Paper m_aPapers[PAPER_COLOR_COUNT]; // ������ 4��
	PAPER_COLOR m_eSelectedColor; // ���� ���õ� �÷�

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
