#pragma once
#include "GameDefine.h"

class Jar
{
private:
	int m_ix, m_iy; // �׷��� ��ġ(�»���� �ƴ� �߽���ġ)
	int m_iWidth, m_iHeight;
	const float m_iMultiple = 2.0f; // ���� �̹����� �� �� ũ��� �׸���	

	LPCWSTR m_aAnimation[2];

	RECT m_Rect;

	//Ÿ��üũ��
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fAnimTick; // �ִϸ��̼��� �� �ʸ��� �ٲ�� ����
public:
	RECT getRect();
	void init(int x, int y);
	void update(int x, int y);
	void draw();
	Jar();
	~Jar();
};