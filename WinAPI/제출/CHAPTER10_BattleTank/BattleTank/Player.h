#pragma once
#include "GlobalDefine.h"
#include "GameObject.h"
#include "Bullet.h"
#include "BulletManager.h"

class Player : public GameObject
{
private:
	MOVE_STATE m_eState;

	LPCWSTR m_aAnimations[16];
	bool m_bAutoMode;

	//Ÿ��üũ��
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fAnimTick; // �����϶� �ִϸ��̼��� ���ʸ��� �ٲ�� ����
	float m_fBulletTime;
	float m_fAutoMoveTick;

	int m_iAnimIndex = 0;
	int t = 0;

	LPCWSTR getShape(); // �׷��� ����� ��ȯ�Ѵ�.	
	BulletManager m_BulletManager;
	
public:
	const float multifly = 1.0f;
	void init(int x, int y, RECT mapRect);
	void draw();
	POINT update(Block* map[][MAP_HEIGHT]);
	void setState(MOVE_STATE state);
	MOVE_STATE getState();
	RECT getRect();
	bool setAutoMode(bool autoMode);
	
	void shootBullet();
	Player();
	~Player();
};