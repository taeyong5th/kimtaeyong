#include <Windows.h>
#include "EngineMain.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "GameSelectScene.h"
#include "AirplaneGameScene.h"
#include "ConfettiGameScene.h"
#include "GameScene.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	//���� ��ü�� �����ϰ� Ÿ��Ʋ�� ������ ����� �־��ش�.
	JEngine::EngineMain engine("EngineTest", 410, 647);
	//���� ����Ѵ�. ù��° ����ϴ� ���� �ʱ�ȭ���� �ȴ�.
	JEngine::SceneManager::GetInstance()->RegistScene(new TitleScene); 
	JEngine::SceneManager::GetInstance()->RegistScene(new GameScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new GameSelectScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new AirplaneGameScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new ConfettiGameScene);

	//���� ����
	return engine.StartEngine(hInstance);
}