#pragma once
#include "GameDefine.h"

class Jar : public CircusObject
{
private:
	LPCWSTR m_aAnimation[2];
	float m_fAnimTick; // �ִϸ��̼��� �� �ʸ��� �ٲ�� ����

	RECT getJarRect();
public:
	// ������Ʈ�� x, y �ʱ� ��ġ�� ���Ѵ�.
	void init(int x, int y) override;
	// camera�� X��ġ�� ���� ȭ����� ��ġ�� �ٽ� ���Ѵ�.
	void update(int cameraX = 0) override;
	// ��Ʈ�� �Ŵ����� Memory DC�� �׸���.
	void draw() override;

	Jar();
	~Jar();
};