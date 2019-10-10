#pragma once
#include "GameDefine.h"

enum FIRE_CIRCLE
{
	FIRE_L,
	FIRE_R
};

enum FIRE_MOVEMENT
{
	FIRE_AUTO_MOVE,
	FIRE_STOP
};

class FireCircle
{
private:
	int m_ix, m_iy, m_iCameraX; // �׷��� ��ġ(�»���� �ƴ� �߽���ġ)
	int m_iWidth, m_iHeight;
	const float m_iMultiple = 2.0f; // ���� �̹����� �� �� ũ��� �׸���
	FIRE_MOVEMENT m_Movement;

	int m_iAnimCount;
	LPCWSTR m_aAnimationL[2];
	LPCWSTR m_aAnimationR[2];

	RECT m_Rect;

	//Ÿ��üũ��
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fAnimTick; // �ִϸ��̼��� �� �ʸ��� �ٲ�� ����
public:
	void init(int x, int y);
	void update(int cameraX);
	void draw(FIRE_CIRCLE loc);
	void setMovement(FIRE_MOVEMENT move);
	RECT getRect();
	FireCircle();
	~FireCircle();
};