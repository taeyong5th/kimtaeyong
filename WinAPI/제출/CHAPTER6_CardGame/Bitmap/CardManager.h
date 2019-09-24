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
	void add(Card* card); // 카드 추가한다.
	void remove(Card* card); // 카드를 삭제한다.
	
	void runClickEvent(HWND hwnd, int x, int y); // x, y 좌표 최상단에 있는 비트맵 이미지의 이벤트함수를 호출한다.
};