#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "SingleTon.h"

class FeverMode : public SingleTon<FeverMode>
{
private:
	JEngine::BitMap* m_pFeverEffect;
	JEngine::BitMap* m_pFeverBack;
	JEngine::BitMap* m_pFeverBar;

	int m_iFeverScore;
	const int m_iFeverScoreMax = 10;

	float m_fFeverTime; // 피버모드가 켜진시간
	float m_fFeverAnimTime; // 깜박임 애니메이션 시간
	const float m_fFeverLimitTime = 5.0f;
	const float m_fFeverAnimTick = 0.3f; // 몇초마다 깜박거릴지

	bool m_bFeverDraw; // 피버효과 깜박임 그릴지 결정
	bool m_bFeverMode; // 피버모드가 켜졌는지

public:
	FeverMode();
	~FeverMode();
	void init(); 
	void update(float fEtime);
	void draw();
	void addFever(int score = 1);
	bool isFeverMode();
};