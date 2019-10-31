#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"

class Flight
{
private:
	JEngine::BitMap* m_pBitmap;
	JEngine::BitMap* m_pExplosion[3];
	JEngine::POINT m_curPoint; // 현재 위치 좌표
	JEngine::RECT m_BodyRect;
	JEngine::RECT m_WingRect;
	bool m_bisDie;
	int m_iScore;

	int m_iExplosionAnimIndex;
	float m_fExplosionTime;
	const float m_fExplosionAnimTick = 0.15f;
	const float m_fExplosionLimitTime = 1.5f;

public:
	void init();
	void setPos(JEngine::POINT flighitPoint);	
	void update(float fETime);
	void draw();
	JEngine::POINT getPoint();
	bool isCollision(JEngine::RECT rect);
	bool isCollision(JEngine::POINTF rect);
	void setDie(bool isDie);
	void addScore(int score);
	int getScore();

	Flight();
	~Flight();
};