#pragma once
#include "GlobalDefine.h"
#include "GameObject.h"

class Item : public GameObject
{
private:

	LPCWSTR getShape() override; // �׷��� ����� ��ȯ�Ѵ�.	

public:
	void init(int x, int y, RECT mapRect) override; 
	void draw() override;	
	RECT getRect() override;
	Item();
	~Item();
};