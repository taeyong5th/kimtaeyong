#pragma once
#include "GameDefine.h"

enum FIRE_CIRCLE
{
	FIRE_L,
	FIRE_R
};

class FireCircle
{
private:
	int m_ix, m_iy, m_iCameraX; // 그려질 위치(좌상단이 아닌 중심위치)
	const float m_iMultiple = 2.0f; // 원본 이미지의 몇 배 크기로 그릴지

	int m_iAnimCount;
	LPCWSTR m_aAnimationL[2];
	LPCWSTR m_aAnimationR[2];

	//타임체크용
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fAnimTick; // 애니메이션을 몇 초마다 바뀌게 할지
public:
	void init(int x, int y);
	void update(int cameraX);
	void draw(FIRE_CIRCLE loc);
	FireCircle();
	~FireCircle();
};