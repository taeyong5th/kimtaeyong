#pragma once
#include "GameDefine.h"

enum JAR_ANIM
{
	JAR_ANIM_START,
	JAR_ANIM_STOP
};

class Jar : public CircusObject
{
private:
	JAR_ANIM m_eAnim;
	LPCWSTR m_aAnimation[2];
	float m_fAnimTick; // �ִϸ��̼��� �� �ʸ��� �ٲ�� ����
	int m_iAnimCount;
	RECT getJarRect();
public:
	// ������Ʈ�� x, y �ʱ� ��ġ�� ���Ѵ�.
	void init(int x, int y) override;
	// camera�� X��ġ�� ���� ȭ����� ��ġ�� �ٽ� ���Ѵ�.
	void update(int cameraX = 0) override;
	// ��Ʈ�� �Ŵ����� Memory DC�� �׸���.
	void draw() override;
	// �ִϸ��̼� ����
	void setAnimation(JAR_ANIM anim);

	Jar();
	~Jar();
};