#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "Label.h"

class GameSelectScene : public JEngine::Scene
{
private:
	JEngine::BitMap* m_pBack;
	int m_iAirplaneScore, m_iConfettiScore;
	JEngine::Label m_AirplaneScoreLabel;
	JEngine::Label m_ConfettiScoreLabel;
	std::function<bool()> clickEvent;

public:
	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();
	bool OnClick();

	GameSelectScene();
	virtual ~GameSelectScene();
};

