#pragma once
#include "GameDefine.h"

class Jar
{
private:
	int m_ix, m_iy; // 그려질 위치(좌상단이 아닌 중심위치)
	int m_iWidth, m_iHeight;
	const float m_iMultiple = 2.0f; // 원본 이미지의 몇 배 크기로 그릴지	

	LPCWSTR m_aAnimation[2];

	RECT m_Rect;

	//타임체크용
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fAnimTick; // 애니메이션을 몇 초마다 바뀌게 할지
public:
	RECT getRect();
	void init(int x, int y);
	void update(int x, int y);
	void draw();
	Jar();
	~Jar();
};