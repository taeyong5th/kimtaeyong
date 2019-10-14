#pragma once
#include "GameDefine.h"

class Meter : public CircusObject
{
private:
	int m_iNumber; // 몇 m인지
	NumberBitmap m_NumberUI;
public:
	// 오브젝트의 x, y 초기 위치를 정한다.
	void init(int x, int y) override;
	void init(int x, int y, int mapWidth);
	// camera의 X위치에 따라 화면상의 위치를 다시 정한다.
	void update(int cameraX = 0) override;
	// 비트맵 매니저의 Memory DC에 그린다.
	void draw() override;

	Meter();
	~Meter();
};