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
	bool setFlag(); // flag�� �ȴ´�. �̹� ���������� flag�� �����Ѵ�.
	bool isFlag(); // flag�� �����ִ��� �˻��Ѵ�.
	bool isOpen();
	void open();
	void draw();
	string getShape(); // �׷��� ����� ��ȯ�Ѵ�.
private:
	MapDraw m_MapDraw;
	int m_ix;
	int m_iy;
	int m_iData; // -1�̸� ���� 0 �̻��̸� ���� ����
	bool m_bIsOpen; // �ش� ��ġ�� �����ߴ���
	bool m_bFlag; // �ش� ��ġ�� flag�� �ȾҴ���
		
};