#include "ConfettiGameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include "defines.h"


void ConfettiGameScene::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_SPACE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//ColoredPaperBack.bmp");
	m_pRedPaper = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//ColoredPaperRed.bmp");
	m_pRedPaper->SetAnchor(JEngine::ANCHOR_CENTER);

	for (int i = 0; i < PAPER_COLOR_COUNT; ++i)
	{
		m_aPapers[i].init((PAPER_COLOR)i);
	}

	x = 208;
	y = 354;
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
			}
			else if (m_LastClick.x > 263 && m_LastClick.x < 343 && m_LastClick.y > 300 && m_LastClick.y < 400)
			{
				x = m_LastClick.x;
				y = 354;
			}
			else if (m_LastClick.x > 155 && m_LastClick.x < 260 && m_LastClick.y > 403 && m_LastClick.y < 500)
			{
				x = 208;
				y = m_LastClick.y;
			}
			else if (m_LastClick.x > 70 && m_LastClick.x < 153 && m_LastClick.y > 300 && m_LastClick.y < 400)
			{
				x = m_LastClick.x;
				y = 354;
			}
		}
		
	}
	else if (JEngine::InputManager::GetInstance()->isKeyUp(VK_LBUTTON))
	{
		if (isClicked)
		{
			isClicked = false;
			m_iPaperIdx = rand() % PAPER_COLOR_COUNT;
			x = 208;
			y = 354;
		}		
	}
	return false;
}

void ConfettiGameScene::Update(float fETime)
{
}

void ConfettiGameScene::Draw(HDC hdc)
{
	m_pBack->Draw(0, 0);
	//m_pRedPaper->Draw(x, y);

	m_aPapers[2].draw(213, 358);
	m_aPapers[m_iPaperIdx].draw(x, y);
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
