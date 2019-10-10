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

class FireCircle : public CircusObject
{
private:
	FIRE_MOVEMENT m_Movement;

	int m_iAnimCount;
	LPCWSTR m_aAnimationL[2];
	LPCWSTR m_aAnimationR[2];

	float m_fAnimTick; // 애니메이션을 몇 초마다 바뀌게 할지

	RECT getFireRect();
public:
	// 오브젝트의 x, y 초기 위치를 정한다.
	void init(int x, int y) override;
	// camera의 X위치에 따라 화면상의 위치를 다시 정한다.
	void update(int cameraX = 0) override;
	// 비트맵 매니저의 Memory DC에 그린다.
	void draw() override;
	void draw(FIRE_CIRCLE loc);
	void setMovement(FIRE_MOVEMENT move);
	FireCircle();
	~FireCircle();
};