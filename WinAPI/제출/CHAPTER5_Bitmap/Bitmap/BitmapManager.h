#pragma once
#include <Windows.h>
#include <list>
#include "Bitmap.h"
#include "Singleton.h"

class BitmapManager : public Singleton<BitmapManager>
{
private:
	std::list<Bitmap*> m_BitmapList;

public:
	BitmapManager();
	~BitmapManager();

	void add(Bitmap *bitmap); // ��Ʈ���� �߰��Ѵ�.
	void remove(Bitmap *bitmap); // ��Ʈ���� �����Ѵ�.
	int getSize(); // ��ϵ� ��Ʈ�� ������ ��ȯ�Ѵ�.
	void draw(HDC hdc); // ��Ʈ�� ����Ʈ�� ����� �̹����� ��� �׸���.
	void runClickEvent(HWND hwnd, int x, int y); // x, y ��ǥ �ֻ�ܿ� �ִ� ��Ʈ�� �̹����� �̺�Ʈ�Լ��� ȣ���Ѵ�.
};