#include "AirplaneGameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include "defines.h"


void AirplaneGameScene::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);

	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//FlightGameBack.bmp");
}

bool AirplaneGameScene::Input(float fETime)
{
	// ESC 누르면 게임선택 화면으로 돌아감
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
	{
		JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAME_SELECT);
	}

	return false;
}

void AirplaneGameScene::Update(float fETime)
{
}

void AirplaneGameScene::Draw(HDC hdc)
{
	m_pBack->Draw(0, 0);
}

void AirplaneGameScene::Release()
{
}

bool AirplaneGameScene::OnClick()
{
	return false;
}

AirplaneGameScene::AirplaneGameScene()
{
}

AirplaneGameScene::~AirplaneGameScene()
{
}
