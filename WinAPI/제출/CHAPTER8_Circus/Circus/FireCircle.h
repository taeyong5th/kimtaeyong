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

	float m_fAnimTick; // �ִϸ��̼��� �� �ʸ��� �ٲ�� ����

	RECT getFireRect();
public:
	// ������Ʈ�� x, y �ʱ� ��ġ�� ���Ѵ�.
	void init(int x, int y) override;
	// camera�� X��ġ�� ���� ȭ����� ��ġ�� �ٽ� ���Ѵ�.
	void update(int cameraX = 0) override;
	// ��Ʈ�� �Ŵ����� Memory DC�� �׸���.
	void draw() override;
	void draw(FIRE_CIRCLE loc);
	void setMovement(FIRE_MOVEMENT move);
	FireCircle();
	~FireCircle();
};