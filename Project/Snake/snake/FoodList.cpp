#include "FoodList.h"

void FoodList::addFood()
{
	srand(time(NULL));
	int x = rand() % (m_iWidth - 2) + 1;
	int y = rand() % (m_iHeight - 2) + 1;

	Block *new_food = new Block(BLOCK_STATE_FOOD, x, y);
	new_food->draw();
}

void FoodList::removeFood()
{
}

FoodList::FoodList()
{
	m_iWidth = WINDOW_SIZE_WIDTH / 2;
	m_iHeight = WINDOW_SIZE_HEIGHT - 3;
	head = NULL;
}

FoodList::~FoodList()
{
}
