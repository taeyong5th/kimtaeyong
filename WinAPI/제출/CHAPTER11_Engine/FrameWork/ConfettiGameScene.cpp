#include "ConfettiGameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include "FeverMode.h"
#include "ScoreUI.h"
#include "ScoreData.h"

void ConfettiGameScene::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_SPACE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//ColoredPaperBack.bmp");


	m_pTimeBar = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//ColoredPaperTimeBar.bmp");
	m_pTimeOver = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//TimeOver.bmp");

	m_pTimeOver->SetAnchor(JEngine::ANCHOR_CENTER);

	for (int i = 0; i < PAPER_COLOR_COUNT; ++i)
	{
		m_aPapers[i].init((PAPER_COLOR)i);
	}

	m_iScore = 0;
	m_iScoreBonus = 100;
	m_fPlayTime = 0.0f;
	m_fGameOverTime = 0.0f;

	m_eState = GAME_STATE_PLAY;
	m_iPaperX = 208;
	m_iPaperY = 354;
	m_eSelectedColor = PAPER_COLOR_NONE;
	m_iPaperIdx = rand() % PAPER_COLOR_COUNT;

	FeverMode::GetInstance()->init();
	ScoreUI::GetInstance()->init();
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
				m_iPaperX = 208;
				m_iPaperY = m_LastClick.y;
				m_eSelectedColor = PAPER_COLOR_GREEN;
			}
			else if (m_LastClick.x > 263 && m_LastClick.x < 343 && m_LastClick.y > 300 && m_LastClick.y < 400)
			{
				m_iPaperX = m_LastClick.x;
				m_iPaperY = 354;
				m_eSelectedColor = PAPER_COLOR_RED;
			}
			else if (m_LastClick.x > 155 && m_LastClick.x < 260 && m_LastClick.y > 403 && m_LastClick.y < 500)
			{
				m_iPaperX = 208;
				m_iPaperY = m_LastClick.y;
				m_eSelectedColor = PAPER_COLOR_YELLOW;
			}
			else if (m_LastClick.x > 70 && m_LastClick.x < 153 && m_LastClick.y > 300 && m_LastClick.y < 400)
			{
				m_iPaperX = m_LastClick.x;
				m_iPaperY = 354;
				m_eSelectedColor = PAPER_COLOR_BLUE;
			}
		}
	}
	else if (JEngine::InputManager::GetInstance()->isKeyUp(VK_LBUTTON))
	{
		if (isClicked)
		{
			// 맞췄을때
			if (m_eSelectedColor == m_aPapers[m_iPaperIdx].getColor())
			{
				FeverMode::GetInstance()->addFever(2);
				m_iScore += m_iScoreBonus;
				m_iScoreBonus += 100;
				m_iPaperIdx = rand() % PAPER_COLOR_COUNT;
			}
			// 틀렸을때
			else
			{
				m_iScoreBonus = 100;
			}

			isClicked = false;
			m_eSelectedColor = PAPER_COLOR_NONE;
			m_iPaperX = 208;
			m_iPaperY = 354;
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
		FeverMode::GetInstance()->update(fETime);
		ScoreUI::GetInstance()->update(fETime, m_iScore);
		break;
	case GAME_STATE_OVER:
		m_fGameOverTime += fETime;
		if (m_fGameOverTime >= m_fGameOverLimitTime)
		{
			int bestScore = ScoreData::GetInstance()->loadScore(CONFETTI_BEST_SCORE);
			if (m_iScore > bestScore)
			{
				ScoreData::GetInstance()->saveScore(CONFETTI_BEST_SCORE, m_iScore);
			}
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

	FeverMode::GetInstance()->draw();
	ScoreUI::GetInstance()->draw(180, 20);
	switch (m_eState)
	{		
	case GAME_STATE_PLAY:
		// 색종이 그리기
		m_aPapers[m_iPaperIdx].draw(m_iPaperX, m_iPaperY);		
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
