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
		// x, y Ŭ���� ���� �ִ� ī�� �� ���� ���� �׷��� ī���� �̺�Ʈ �Լ��� ȣ���Ѵ�.
		if ((*it)->isVaildRange(x, y))
		{
			(*it)->runClickEvent(hwnd, x, y);
			break;
		}
	}
}


