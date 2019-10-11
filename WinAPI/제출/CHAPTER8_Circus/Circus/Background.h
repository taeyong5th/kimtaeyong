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
	int m_ix, m_iy; // ����� �׷��� ��ġ
	const float m_iMultiple = 2.0f; // ���� �̹����� �� ��ũ��� �׸���	
	BG_ANIM m_eAnim;

	LPCWSTR m_aAnimation[2]; 
	int m_iAnimCount;

	//Ÿ��üũ��
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fAnimTick; // �ִϸ��̼��� �� �ʸ��� �ٲ�� ����
	
public:
	void init(int x, int y = 0);
	void update(int x, int y = 0);
	void draw();
	void setAnimState(BG_ANIM anim);
	Background();
	~Background();
};
