#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "Paper.h"

class ConfettiGameScene : public JEngine::Scene
{
private:
	JEngine::BitMap* m_pBack;
	JEngine::BitMap* m_pRedPaper;
	JEngine::POINT m_FirstClick;
	JEngine::POINT m_LastClick;
	int x, y;
	int m_iPaperIdx;
	Paper m_aPapers[PAPER_COLOR_COUNT];

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
