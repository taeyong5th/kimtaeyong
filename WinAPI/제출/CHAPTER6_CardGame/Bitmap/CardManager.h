#pragma once
#include <Windows.h>
#include <list>
#include <vector>
#include "Card.h"

class CardManager
{
private:
	std::vector<Card*> m_ChoosedCardList; // ������ ī��(�ִ� 2��)
public:
	std::list<Card*> m_CardList; // ��� ī�� ����Ʈ
public:	
	CardManager();
	~CardManager();
	size_t chooseCount(); // ������ ī�� ����
	void choose(Card* card); // ī�带 �����Ѵ�.
	bool isMatched(); // �ΰ��� ī�尡 ������ Ȯ��
	void update(); // ������ 2���� ī�� ���¸� ������Ʈ
	void add(Card* card); // ī�� �߰��Ѵ�.
	void remove(Card* card); // ī�带 �����Ѵ�.
	void runClickEvent(HWND hwnd, int x, int y); // x, y ��ǥ �ֻ�ܿ� �ִ� ��Ʈ�� �̹����� �̺�Ʈ�Լ��� ȣ���Ѵ�.
};