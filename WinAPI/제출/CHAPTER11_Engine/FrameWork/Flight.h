#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"

class Flight
{
private:
	JEngine::BitMap* m_pBitmap;
	JEngine::POINT m_curPoint; // ���� ��ġ ��ǥ
	JEngine::RECT m_BodyRect;
	JEngine::RECT m_WingRect;

public:
	void init();
	void setPos(JEngine::POINT flighitPoint);	
	void update(float fETime);
	void draw();
	JEngine::POINT getPoint();
	bool isCollision(JEngine::RECT rect);
	bool isCollision(JEngine::POINTF rect);

	Flight();
	~Flight();
};