#pragma once
#include "GlobalDefine.h"

class Block
{
public:
	Block(int x, int y);
	~Block();
	int getData();
	void setData(int data);
	bool setFlag(); // flag�� �ȴ´�. �̹� ���������� flag�� �����Ѵ�.
	bool isFlag(); // flag�� �����ִ��� �˻��Ѵ�.
	bool isOpen();
	void open();
	void draw(int top = 0, int left = 0);
	
private:
	int m_ix;
	int m_iy;
	int m_iData; // -1�̸� ���� 0 �̻��̸� ���� ����
	bool m_bIsOpen; // �ش� ��ġ�� �����ߴ���
	bool m_bFlag; // �ش� ��ġ�� flag�� �ȾҴ���
	
	LPCWSTR getShape(); // �׷��� ����� ��ȯ�Ѵ�.	
};