#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"

class Star
{
private:
	JEngine::BitMap* m_pBitmap;
	JEngine::POINTF m_curPoint; // 현재 위치 좌표
	JEngine::POINT m_FlightPoint; // 총알 생성시 비행기의 위치
	float theta;
	const float m_StarSpeed = 130.0f;
	int m_ixDirection, m_iyDirection;

public:
	void init(JEngine::POINT flighitPoint);
	void draw();
	void update(float fETime);
	JEngine::POINTF getPoint();
	JEngine::RECT getRECT();
	bool isInside(); // 별이 rect 내부에 있는지 검사

	Star();
	~Star();
};