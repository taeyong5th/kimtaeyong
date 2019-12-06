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

	// 핸들정보
	HWND m_hWnd;
			
	// 버튼 이미지
	JEngine::BitMap* m_pBtnStart; // 게임 시작 버튼 이미지
	JEngine::RECT m_BtnStartRect;
	JEngine::BitMap* m_pCircle; // 

	// 바둑돌 이미지
	JEngine::BitMap*	m_pStone[2];	 // 0 = black, 1 = white

	// 마우스의 현재 위치
	JEngine::POINT m_iMousePos;

	// 블럭 하나의 정보
	int m_iBlockWidth, m_iBlockHeight;
	JEngine::BitMap*	m_pBlock;

	// 오목판의 정보	
	JEngine::RECT m_boardRect;

	// 하단 설명
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

