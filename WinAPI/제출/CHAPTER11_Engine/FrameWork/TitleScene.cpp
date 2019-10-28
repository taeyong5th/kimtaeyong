#include "TitleScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include "defines.h"


TitleScene::TitleScene()
{
	m_fTitleX = 444.0f;
	m_fTitleY = 268.0f;

	m_fSpeedX = 200;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_SPACE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LEFT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_RIGHT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//Title.bmp");
	m_pTitle = JEngine::ResoucesManager::GetInstance()->GetBitmap("char.bmp");

	//JEngine::UIManager::GetInstance()->AddButton(10, 20, "OnSelect.bmp", std::bind(&TitleScene::OnClick, this));
	m_pTitle->SetAnchor(JEngine::ANCHOR_CENTER);
}

bool TitleScene::Input(float fETime)
{
	// 게임 선택 화면으로 넘어간다.
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_LBUTTON))
	{
		JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAME_SELECT);
	}
	else if (JEngine::InputManager::GetInstance()->isKeyUp(VK_SPACE))
	{
		JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAME_SELECT);
	}
	else if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
	{
		return true;
	}
		
	return false;
}

void TitleScene::Update(float fETime)
{
	
}

void TitleScene::Draw(HDC hdc)
{
	m_pBack->DrawBitblt(0, 0);	
}

void TitleScene::Release()
{

}

bool TitleScene::OnClick()
{
	JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAME);
	return true;
}