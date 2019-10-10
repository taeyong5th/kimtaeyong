#pragma once
#include "GameDefine.h"

class Goal : public CircusObject
{
private:
	RECT getGoalRect();

public:
	// ������Ʈ�� x, y �ʱ� ��ġ�� ���Ѵ�.
	void init(int x, int y) override;
	// camera�� X��ġ�� ���� ȭ����� ��ġ�� �ٽ� ���Ѵ�.
	void update(int cameraX = 0) override;
	// ��Ʈ�� �Ŵ����� Memory DC�� �׸���.
	void draw() override;
	Goal();
	~Goal();
};