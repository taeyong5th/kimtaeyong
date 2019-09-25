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
	// �̹� ������ ī��� �������� ����
	if (card->isOpened()) return;

	// ������ ī�� ������ 2�� ���ϸ� ���Ϳ� �߰��ϰ� ī�� ����
	if (m_ChoosedCardList.size() < 2)
	{
		m_ChoosedCardList.push_back(card);
		card->open();
	}
}

bool CardManager::isMatched()
{
	if (m_ChoosedCardList.size() < 2) return false;

	// ������ �ΰ��� ī�尡 ���� �̹����� true ����
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
		// x, y Ŭ���� ���� �ִ� ī�� �� ���� ���� �׷��� ī���� �̺�Ʈ �Լ��� ȣ���Ѵ�.
		if ((*it)->isVaildRange(x, y))
		{
			(*it)->runClickEvent(hwnd, x, y);
			break;
		}
	}
}


