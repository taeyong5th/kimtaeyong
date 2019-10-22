#pragma once
#include "GlobalDefine.h"
#include "GameObject.h"

class Bullet : public GameObject
{
private:
	friend class BulletManager;

	LPCWSTR m_aAnimations[5]; // 폭발 애니메이션
	LPCWSTR m_aBulletImage[4]; //  총알 이미지 방향

	//타임체크용
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fAnimTick; // 폭발 애니메이션을 몇초마다 바뀌게 할지

	int m_iAnimIndex = 0;
	
	LPCWSTR getShape() override; // 그려질 모양을 반환한다.	
public:
	const float multifly = 1.0f;
	void init(int x, int y, RECT mapRect) override;
	void draw() override;
	void update();
	RECT getRect() override;
	Bullet();
	~Bullet();
};