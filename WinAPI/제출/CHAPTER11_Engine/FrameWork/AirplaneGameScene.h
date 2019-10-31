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
	JEngine::BitMap* m_pFlight;

	GAME_STATE m_eState;

	float m_fPlayTime;
	const float m_fPlayLimitTime = 20.0f;
	float m_fGameOverTime;
	const float m_fGameOverLimitTime = 2.0f;
	float m_fBulletGenTime;
	const float m_fBulletGenLimitTime = 0.6f;
	float m_fStarGenTime;
	const float m_fStarGenLimitTime = 0.8f;

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

