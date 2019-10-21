#pragma once
#include "GlobalDefine.h"
#include "GameObject.h"

class Bullet : public GameObject
{
private:
	friend class BulletManager;
	MOVE_STATE m_eState;

	LPCWSTR m_aAnimations[5]; // ���� �ִϸ��̼�
	LPCWSTR m_aBulletImage[4]; //  �Ѿ� �̹��� ����

	//Ÿ��üũ��
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fAnimTick; // ���� �ִϸ��̼��� ���ʸ��� �ٲ�� ����

	int m_iAnimIndex = 0;
	
	LPCWSTR getShape(); // �׷��� ����� ��ȯ�Ѵ�.	
public:
	const float multifly = 1.0f;
	void init(int x, int y, RECT mapRect);
	void draw();
	void update();
	void setState(MOVE_STATE state);
	MOVE_STATE getState();
	RECT getRect();
	Bullet();
	~Bullet();
};