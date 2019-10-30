#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"

class Bullet
{
private:
	JEngine::BitMap* m_pBitmap;
	JEngine::POINTF m_curPoint; // 현재 위치 좌표
	JEngine::POINT m_FlightPoint; // 총알 생성시 비행기의 위치
	float theta;
	const float m_BulletSpeed = 150.0f;
	int m_ixDirection, m_iyDirection;

public:
	void init(JEngine::POINT flighitPoint);
	void draw();
	void update(float fETime);
	JEngine::POINTF getPoint();
	bool isInside(); // 총알이 rect 내부에 있는지 검사

	Bullet();
	~Bullet();
};