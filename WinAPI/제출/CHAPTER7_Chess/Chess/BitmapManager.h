#pragma once
#include <Windows.h>
#include <map>
#include "Bitmap.h"
#include "Singleton.h"

class BitmapManager : public Singleton<BitmapManager>
{
private:
	std::map<LPCWSTR, Bitmap*> m_BitmapList;

public:
	BitmapManager();
	~BitmapManager();

	void add(Bitmap *bitmap); // ��Ʈ���� �߰��Ѵ�.
	void remove(Bitmap *bitmap); // ��Ʈ���� �����Ѵ�.
	int getSize(); // ��ϵ� ��Ʈ�� ������ ��ȯ�Ѵ�.
	Bitmap* getBitmap(LPCWSTR fileName); // fileName�� ��Ʈ���� ��ȯ�Ѵ�.
	void draw(HDC hdc, LPCWSTR fileName, int x, int y, float px = 1.0f, float py = 1.0f); // fileName�� ��Ʈ�� ������ �׸���. x, y : �׷��� �»���ġ, px, py : ���� ��Ʈ�� �ʺ��� px��,  ������ py ��� �׸�
};