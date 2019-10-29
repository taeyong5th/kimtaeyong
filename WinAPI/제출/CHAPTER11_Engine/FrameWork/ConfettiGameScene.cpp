#include "ConfettiGameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"


void ConfettiGameScene::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_SPACE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//ColoredPaperBack.bmp");


	m_pTimeBar = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//ColoredPaperTimeBar.bmp");
	m_pTimeOver = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//TimeOver.bmp");
	m_pFeverEffect = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//FeverEffect.bmp");
	m_pFeverBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//FeverEffect3.bmp");
	m_pFeverBar1 = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//Fever1.bmp");
	m_pFeverBar2 = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//Fever2.bmp");
	m_pFeverBar3 = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//Fever3.bmp");

	m_pTimeOver->SetAnchor(JEngine::ANCHOR_CENTER);

	for (int i = 0; i < PAPER_COLOR_COUNT; ++i)
	{
		m_aPapers[i].init((PAPER_COLOR)i);
	}

	m_iScore = 0;
	m_iFeverScore = 0;
	m_fPlayTime = 0.0f;
	m_fFeverTime = 0.0f;
	m_fGameOverTime = 0.0f;
	m_fFeverAnimTime = 0.0f;

	m_eState = GAME_STATE_PLAY;
	x = 208;
	y = 354;
	m_bFeverMode = false;
	m_bFeverDraw = false;
	m_eSelectedColor = PAPER_COLOR_NONE;
	m_iPaperIdx = rand() % PAPER_COLOR_COUNT;
}

bool ConfettiGameScene::Input(float fETime)
{
	static bool isClicked = false;
	// ESC 누르면 게임선택 화면으로 돌아감
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
	{
		JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAME_SELECT);
	}
	else if (JEngine::InputManager::GetInstance()->isKeyUp(VK_SPACE))
	{
		
	}
	else if (JEngine::InputManager::GetInstance()->isKeyDown(VK_LBUTTON))
	{
		m_FirstClick = JEngine::InputManager::GetInstance()->GetMousePoint();
		if (m_FirstClick.x > 160 && m_FirstClick.x < 263 && m_FirstClick.y > 297 && m_FirstClick.y < 409)
		{
			isClicked = true;
		}
	}
	else if (JEngine::InputManager::GetInstance()->isKeyPress(VK_LBUTTON))
	{
		if (isClicked)
		{
			m_LastClick = JEngine::InputManager::GetInstance()->GetMousePoint();	

			if (m_LastClick.x > 150 && m_LastClick.x < 260 && m_LastClick.y > 201 && m_LastClick.y < 297)
			{
				x = 208;
				y = m_LastClick.y;
				m_eSelectedColor = PAPER_COLOR_GREEN;
			}
			else if (m_LastClick.x > 263 && m_LastClick.x < 343 && m_LastClick.y > 300 && m_LastClick.y < 400)
			{
				x = m_LastClick.x;
				y = 354;
				m_eSelectedColor = PAPER_COLOR_RED;
			}
			else if (m_LastClick.x > 155 && m_LastClick.x < 260 && m_LastClick.y > 403 && m_LastClick.y < 500)
			{
				x = 208;
				y = m_LastClick.y;
				m_eSelectedColor = PAPER_COLOR_YELLOW;
			}
			else if (m_LastClick.x > 70 && m_LastClick.x < 153 && m_LastClick.y > 300 && m_LastClick.y < 400)
			{
				x = m_LastClick.x;
				y = 354;
				m_eSelectedColor = PAPER_COLOR_BLUE;
			}
		}
	}
	else if (JEngine::InputManager::GetInstance()->isKeyUp(VK_LBUTTON))
	{
		if (isClicked)
		{
			if (m_eSelectedColor == m_aPapers[m_iPaperIdx].getColor())
			{
				m_iFeverScore += 400;
				if (m_bFeverMode)
				{
					m_fFeverTime -= 0.25f;
				}
			}

			isClicked = false;
			m_eSelectedColor = PAPER_COLOR_NONE;
			m_iPaperIdx = rand() % PAPER_COLOR_COUNT;			
			x = 208;
			y = 354;
		}
	}
	return false;
}

void ConfettiGameScene::Update(float fETime)
{
	switch (m_eState)
	{
	case GAME_STATE_PLAY:
		m_fPlayTime += fETime;
		// 제한시간 끝나면 게임오버
		if (m_fPlayTime >= m_fPlayLimitTime)
		{
			m_fPlayTime = m_fPlayLimitTime;
			m_eState = GAME_STATE_OVER;
		}

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
			m_fFeverTime += fETime;
			m_fFeverAnimTime += fETime;
			if (m_fFeverAnimTime > 0.3f)
			{
				m_fFeverAnimTime = 0.0f;
				m_bFeverDraw = !m_bFeverDraw;
			}
		}
		else
		{
			m_bFeverDraw = false;
		}
		break;
	case GAME_STATE_OVER:
		m_fGameOverTime += fETime;
		if (m_fGameOverTime >= m_fGameOverLimitTime)
		{
			JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAME_SELECT);
		}
		break;
	default:
		break;
	}


	
}

void ConfettiGameScene::Draw(HDC hdc)
{
	// 배경, 하단 시간바 그리기
	m_pBack->Draw(0, 0);
	m_pTimeBar->Draw(23, 620, m_fPlayTime / m_fPlayLimitTime, 1.0f);

	// 피버모드 게이지 그리기
	if (m_bFeverMode)
	{
		m_pFeverBar1->Draw(20, 51, 1.0f, 1.0f, 0.0f, 0.0f, (m_fFeverLimitTime - m_fFeverTime) / m_fFeverLimitTime, 1.0f);
	}
	else
	{
		m_pFeverBar1->Draw(20, 51, 1.0f, 1.0f, 0.0f, 0.0f, ((float)m_iFeverScore / (float)m_iFeverScoreMax), 1.0f);
	}

	
	switch (m_eState)
	{		
	case GAME_STATE_PLAY:
		// 색종이 그리기
		m_aPapers[m_iPaperIdx].draw(x, y);
		if (m_bFeverDraw)
			m_pFeverBack->Draw(0, 0);
		break;
	case GAME_STATE_OVER:
		// 타임오버 이미지 그리기
		m_pTimeOver->Draw(213, 350);
		break;
	default:
		break;
	}	

}

void ConfettiGameScene::Release()
{
}

bool ConfettiGameScene::OnClick()
{
	return false;
}

ConfettiGameScene::ConfettiGameScene()
{
}

ConfettiGameScene::~ConfettiGameScene()
{
}
