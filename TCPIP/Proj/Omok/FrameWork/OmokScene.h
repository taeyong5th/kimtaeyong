#pragma once
#include <windows.h>
#include <process.h> 
#include "JEngine.h"
#include "../Server/defines.h"
#include "Label.h"

class OmokScene : public JEngine::Scene
{
private:

	WSADATA wsaData;
	SOCKET hSock;
	SOCKADDR_IN servAdr;
	HANDLE hSndThread, hRcvThread;

	// �ڵ�����
	HWND m_hWnd;
			
	// ��ư �̹���
	JEngine::BitMap* m_pBtnStart; // ���� ���� ��ư �̹���
	JEngine::RECT m_BtnStartRect;
	JEngine::BitMap* m_pCircle; // 

	// �ٵϵ� �̹���
	JEngine::BitMap*	m_pStone[2];	 // 0 = black, 1 = white

	// ���콺�� ���� ��ġ
	JEngine::POINT m_iMousePos;

	// �� �ϳ��� ����
	int m_iBlockWidth, m_iBlockHeight;
	JEngine::BitMap*	m_pBlock;

	// �������� ����	
	JEngine::RECT m_boardRect;

	// �ϴ� ����
	JEngine::BitMap* m_pWhiteBar;
	JEngine::Label label;	

	std::function<bool()> clickEvent;

	//
	float m_fGameOverTime;	

public:
	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();

	//static unsigned WINAPI SendMsg(void* arg);
	//static unsigned WINAPI RecvMsg(void* arg);

	OmokScene();
	virtual ~OmokScene();
};

