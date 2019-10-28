#include "GameSelectScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include "defines.h"

void GameSelectScene::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//GameSelect.bmp");

}

bool GameSelectScene::Input(float fETime)
{
	// ESC ������ ó�� ȭ������ ���ư�
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
