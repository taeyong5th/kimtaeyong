#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "defines.h"
#include "Flight.h"
#include "BulletManager.h"
#include "StarManager.h"

class AirplaneGameScene : public JEngine::Scene
{
private:
	Flight m_flight;

	JEngine::BitMap* m_pBack;
	JEngine::BitMap* m_pTimeBar;
	JEngine::BitMap* m_pTimeOver;
	JEngine::BitMap* m_pFeverEffect;
	JEngine::BitMap* m_pFeverBack;
	JEngine::BitMap* m_pFeverBar1;
	JEngine::BitMap* m_pFeverBar2;
	JEngine::BitMap* m_pFeverBar3;
	JEngine::BitMap* m_pFlight;
	JEngine::BitMap* m_pStar1;
	JEngine::BitMap* m_pStar2;
	JEngine::BitMap* m_pStar3;

	int m_iScore;
	int m_iFeverScore;
	const int m_iFeverScoreMax = 1000;
	int m_iPaperIdx;

	GAME_STATE m_eState;

	float m_fFeverAnimTime;

	float m_fPlayTime;
	const float m_fPlayLimitTime = 225.0f;
	float m_fFeverTime;
	const float m_fFeverLimitTime = 5.0f;
	float m_fGameOverTime;
	const float m_fGameOverLimitTime = 2.0f;
	float m_fBulletGenTime;
	const float m_fBulletGenLimitTime = 0.3f;
	float m_fStarGenTime;
	const float m_fStarGenLimitTime = 0.5f;
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

	AirplaneGameScene();
	virtual ~AirplaneGameScene();
};

