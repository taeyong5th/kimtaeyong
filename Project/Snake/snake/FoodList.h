#pragma once
#include "MapDraw.h"
#include "Block.h"

class FoodList
{
private:
	int m_iWidth, m_iHeight;
	Block *head;

public:
	void addFood();
	void removeFood();
	FoodList();
	~FoodList();

};