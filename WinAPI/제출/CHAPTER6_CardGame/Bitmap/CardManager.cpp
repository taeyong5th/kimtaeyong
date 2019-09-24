#include "CardManager.h"

CardManager::CardManager()
{
}

CardManager::~CardManager()
{
}

void CardManager::add(Card* card)
{
	m_CardList.push_back(card);
}

void CardManager::remove(Card* card)
{
	m_CardList.remove(card);
}

void CardManager::runClickEvent(HWND hwnd, int x, int y)
{
	std::list<Card*>::reverse_iterator it;

	for (it = m_CardList.rbegin(); it != m_CardList.rend(); ++it)
	{
		// x, y 클릭된 곳에 있는 카드 중 가장 위에 그려진 카드의 이벤트 함수만 호출한다.
		if ((*it)->isVaildRange(x, y))
		{
			(*it)->runClickEvent(hwnd, x, y);
			break;
		}
	}
}


