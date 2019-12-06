#include <Windows.h>
#include "EngineMain.h"
#include "SceneManager.h"
#include "OmokScene.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	//���� ��ü�� �����ϰ� Ÿ��Ʋ�� ������ ����� �־��ش�.
	JEngine::EngineMain engine("Omok", 400, 416);
	//���� ����Ѵ�. ù��° ����ϴ� ���� �ʱ�ȭ���� �ȴ�.
	JEngine::SceneManager::GetInstance()->RegistScene(new OmokScene); 

	//���� ����
	return engine.StartEngine(hInstance);
}