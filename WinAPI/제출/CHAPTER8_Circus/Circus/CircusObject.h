#pragma once
#include "GameDefine.h"

class CircusObject
{

protected:
	int m_ix, m_iy, m_iCameraX; // 그려질 위치(좌상단이 아닌 중심위치)
	int m_iWidth, m_iHeight;
	const float m_iMultiple = 2.0f; // 원본 이미지의 몇 배 크기로 그릴지

	std::vector<RECT> m_RectList; // 충돌을 체크할 RECT 모음

	//타임체크용
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
public:
	// object와 충돌하는지 검사, 충돌하면 true 아니면 false
	bool isCollision(CircusObject* object);
	// 오브젝트의 x, y 초기 위치를 정한다.
	virtual void init(int x, int y) = 0;
	// camera의 X위치에 따라 화면상의 위치를 다시 정한다.
	virtual void update(int cameraX = 0) = 0;
	// 비트맵 매니저의 Memory DC에 그린다.
	virtual void draw() = 0;

	CircusObject();
	virtual ~CircusObject();
};
