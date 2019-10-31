#include "FeverMode.h"
#include "ResoucesManager.h"

FeverMode::FeverMode()
{
}

FeverMode::~FeverMode()
{
}

void FeverMode::init()
{

	m_pFeverEffect = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//FeverEffect.bmp");
	m_pFeverBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//FeverEffect3.bmp");
	m_pFeverBar = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//Fever1.bmp");

	m_iFeverScore = 0;
	m_fFeverTime = 0.0f;
	m_fFeverAnimTime = 0.0f;

	m_bFeverMode = false;
	m_bFeverDraw = false;
}

void FeverMode::update(float fEtime)
{
	// 피버게이지 가득차면 피버모드
	if (m_iFeverScore >= m_iFeverScoreMax)
	{
		m_bFeverMode = true;
	}
	// 피버 시간 끝나면 피버 모드 종료
	if (m_fFeverTime > m_fFeverLimitTime)
	{
		m_bFeverMode = false;
		m_fFeverTime = 0.0f;
		m_iFeverScore = 0;
	}
	//  피버 모드 0.3초마다 깜박이는 효과
	if (m_bFeverMode)
	{
		m_fFeverTime += fEtime;
		m_fFeverAnimTime += fEtime;
		if (m_fFeverAnimTime > m_fFeverAnimTick)
		{
			m_fFeverAnimTime = 0.0f;
			m_bFeverDraw = !m_bFeverDraw;
		}
	}
	else
	{
		m_bFeverDraw = false;
	}
}

void FeverMode::draw()
{
	if (m_bFeverDraw)
		m_pFeverBack->Draw(0, 0);

	// 피버모드 게이지 그리기
	if (m_bFeverMode)
	{
		m_pFeverBar->Draw(20, 51, 1.0f, 1.0f, 0.0f, 0.0f, (m_fFeverLimitTime - m_fFeverTime) / m_fFeverLimitTime, 1.0f);
	}
	else
	{
		m_pFeverBar->Draw(20, 51, 1.0f, 1.0f, 0.0f, 0.0f, ((float)m_iFeverScore / (float)m_iFeverScoreMax), 1.0f);
	}
}

void FeverMode::addFever(int score)
{
	m_iFeverScore += score;
}

bool FeverMode::isFeverMode()
{
	return m_bFeverMode;
}
