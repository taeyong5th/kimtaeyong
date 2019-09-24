#pragma once
#include <Windows.h>
#include <list>
#include "Card.h"


class CardManager
{
public:
	std::list<Card*> m_CardList;

public:
	CardManager();
	~CardManager();
	void add(Card* card); // ī�� �߰��Ѵ�.
	void remove(Card* card); // ī�带 �����Ѵ�.
	
	void runClickEvent(HWND hwnd, int x, int y); // x, y ��ǥ �ֻ�ܿ� �ִ� ��Ʈ�� �̹����� �̺�Ʈ�Լ��� ȣ���Ѵ�.
};