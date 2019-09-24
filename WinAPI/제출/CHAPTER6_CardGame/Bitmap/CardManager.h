#pragma once
#include <Windows.h>
#include <list>
#include <vector>
#include "Card.h"

class CardManager
{
private:
	std::vector<Card*> m_ChoosedCardList; // 선택한 카드(최대 2개)
public:
	std::list<Card*> m_CardList; // 모든 카드 리스트
public:	
	CardManager();
	~CardManager();
	size_t chooseCount(); // 선택한 카드 개수
	void choose(Card* card); // 카드를 선택한다.
	bool isMatched(); // 두개의 카드가 같은지 확인
	void update(); // 선택한 2개의 카드 상태를 업데이트
	void add(Card* card); // 카드 추가한다.
	void remove(Card* card); // 카드를 삭제한다.
	void runClickEvent(HWND hwnd, int x, int y); // x, y 좌표 최상단에 있는 비트맵 이미지의 이벤트함수를 호출한다.
};