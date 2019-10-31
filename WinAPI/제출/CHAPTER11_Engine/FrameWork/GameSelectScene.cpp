#include "GameSelectScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include "defines.h"
#include "ScoreData.h"

void GameSelectScene::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//GameSelect.bmp");

	m_iAirplaneScore = ScoreData::GetInstance()->loadScore(AIRPLANE_BEST_SCORE);
	m_iConfettiScore = ScoreData::GetInstance()->loadScore(CONFETTI_BEST_SCORE);
	
	m_AirplaneScoreLabel.Init(to_string(m_iAirplaneScore), 112, 288, 0);
	m_ConfettiScoreLabel.Init(to_string(m_iConfettiScore), 112, 205, 0);
	
}

bool GameSelectScene::Input(float fETime)
{
	// ESC 누르면 처음 화면으로 돌아감
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
	{
		JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_TITLE);
	}
	else if (JEngine::InputManager::GetInstance()->isKeyUp(VK_LBUTTON))
	{
		JEngine::POINT p = JEngine::InputManager::GetInstance()->GetMousePoint();
		if (p.x > 322 && p.x < 369 && p.y > 171 && p.y < 222)
		{
			JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_CONFETTI_GAME);
		}
		else if (p.x > 322 && p.x < 369 && p.y > 251 && p.y < 306)
		{
			JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_AIRPLANE_GAME);
		}
	}

	return false;
}

void GameSelectScene::Update(float fETime)
{
}

void GameSelectScene::Draw(HDC hdc)
{
	m_pBack->Draw(0, 0);
	m_AirplaneScoreLabel.Draw();
	m_ConfettiScoreLabel.Draw();
}

void GameSelectScene::Release()
{
}

bool GameSelectScene::OnClick()
{
	return false;
}

GameSelectScene::GameSelectScene()
{
}

GameSelectScene::~GameSelectScene()
{
}
