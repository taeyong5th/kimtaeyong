#pragma once

#include "GameDefine.h"

enum BG_ANIM
{
	BG_ANIM_STOP,
	BG_ANIM_TWINKLE
};

class Background
{
private:
	int m_ix, m_iy; // 배경이 그려질 위치
	const float m_iMultiple = 2.0f; // 원본 이미지의 몇 배크기로 그릴지	
	BG_ANIM m_eAnim;

	LPCWSTR m_aAnimation[2]; 
	int m_iAnimCount;

	//타임체크용
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fAnimTick; // 애니메이션을 몇 초마다 바뀌게 할지
	
public:
	void init(int x, int y = 0);
	void update(int x, int y = 0);
	void draw();
	void setAnimState(BG_ANIM anim);
	Background();
	~Background();
};
