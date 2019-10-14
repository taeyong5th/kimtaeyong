#pragma once
#include "GameDefine.h"

class Meter : public CircusObject
{
private:
	int m_iNumber; // �� m����
	NumberBitmap m_NumberUI;
public:
	// ������Ʈ�� x, y �ʱ� ��ġ�� ���Ѵ�.
	void init(int x, int y) override;
	void init(int x, int y, int mapWidth);
	// camera�� X��ġ�� ���� ȭ����� ��ġ�� �ٽ� ���Ѵ�.
	void update(int cameraX = 0) override;
	// ��Ʈ�� �Ŵ����� Memory DC�� �׸���.
	void draw() override;

	Meter();
	~Meter();
};