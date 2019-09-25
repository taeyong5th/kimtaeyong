#include "CardManager.h"

CardManager::CardManager()
{
	m_ChoosedCardList.reserve(2);
}

CardManager::~CardManager()
{
	
}

std::list<Card*> CardManager::getCardList()
{
	return m_CardList;
}

size_t CardManager::chooseCount()
{
	return m_ChoosedCardList.size();
}

void CardManager::choose(Card* card)
{
	// 이미 오픈한 카드는 선택하지 않음
	if (card->isOpened()) return;

	// 선택한 카드 개수가 2개 이하면 벡터에 추가하고 카드 오픈
	if (m_ChoosedCardList.size() < 2)
	{
		m_ChoosedCardList.push_back(card);
		card->open();
	}
}

bool CardManager::isMatched()
{
	if (m_ChoosedCardList.size() < 2) return false;

	// 선택한 두개의 카드가 같은 이미지면 true 리턴
	if (m_ChoosedCardList[0]->getBitmapID() == m_ChoosedCardList[1]->getBitmapID())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CardManager::update()
{
	if (m_ChoosedCardList.size() < 2) return;

	if (m_ChoosedCardList[0]->getBitmapID() == m_ChoosedCardList[1]->getBitmapID())
	{
		m_ChoosedCardList[0]->setState(CARD_MATCHED);
		m_ChoosedCardList[1]->setState(CARD_MATCHED);
		m_ChoosedCardList.clear();
	}
	else
	{
		m_ChoosedCardList[0]->setState(CARD_CLOSED);
		m_ChoosedCardList[1]->setState(CARD_CLOSED);
		m_ChoosedCardList.clear();
	}
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


