#pragma once
#include "Mecro.h"
#include "MapDraw.h"


class Element
{
public:
	Element(int x, int y);
	~Element();
	int getData();
	void setData(int data);
	bool setFlag(); // flag를 꽂는다. 이미 꽂혀있으면 flag를 해제한다.
	bool isFlag(); // flag가 꽂혀있는지 검사한다.
	bool isOpen();
	void open();
	void draw();
	string getShape(); // 그려질 모양을 반환한다.
private:
	MapDraw m_MapDraw;
	int m_ix;
	int m_iy;
	int m_iData; // -1이면 지뢰 0 이상이면 지뢰 개수
	bool m_bIsOpen; // 해당 위치를 오픈했는지
	bool m_bFlag; // 해당 위치에 flag를 꽂았는지
		
};