#pragma once
#include "GlobalDefine.h"
#include "GameObject.h"

class Item : public GameObject
{
private:

	LPCWSTR getShape() override; // 그려질 모양을 반환한다.	

public:
	void init(int x, int y, RECT mapRect) override; 
	void draw() override;	
	RECT getRect() override;
	Item();
	~Item();
};