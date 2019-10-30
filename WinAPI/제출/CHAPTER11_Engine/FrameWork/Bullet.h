#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"

class Bullet
{
private:
	JEngine::BitMap* m_pBitmap;
	JEngine::POINTF m_curPoint; // ���� ��ġ ��ǥ
	JEngine::POINT m_FlightPoint; // �Ѿ� ������ ������� ��ġ
	float theta;
	const float m_BulletSpeed = 150.0f;
	int m_ixDirection, m_iyDirection;

public:
	void init(JEngine::POINT flighitPoint);
	void draw();
	void update(float fETime);
	JEngine::POINTF getPoint();
	bool isInside(); // �Ѿ��� rect ���ο� �ִ��� �˻�

	Bullet();
	~Bullet();
};