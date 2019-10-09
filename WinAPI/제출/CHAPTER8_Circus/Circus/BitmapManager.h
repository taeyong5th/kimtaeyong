#pragma once
#include <Windows.h>
#include <map>
#include "Bitmap.h"
#include "Singleton.h"

class BitmapManager : public Singleton<BitmapManager>
{
private:
	std::map<LPCWSTR, Bitmap*> m_BitmapList;
	HDC m_MemDC;
	HBITMAP m_hBitmap; // ��Ʈ�� ����
	int m_iWidth, m_iHeight;
public:
	BitmapManager();
	~BitmapManager();
	void init(HDC hdc, int width, int height);

	void add(Bitmap *bitmap); // ��Ʈ���� �߰��Ѵ�.
	void remove(Bitmap *bitmap); // ��Ʈ���� �����Ѵ�.
	int getSize(); // ��ϵ� ��Ʈ�� ������ ��ȯ�Ѵ�.
	Bitmap* getBitmap(LPCWSTR fileName); // fileName�� ��Ʈ���� ��ȯ�Ѵ�.
	// �׷��� �̹����� �޸�DC�� �׸���.
	// x, y : �׷��� �»���ġ, px, py : ���� ��Ʈ�� �ʺ��� px��, ������ py ��� �׸�
	bool prepare(LPCWSTR fileName, int x, int y, float px = 1.0f, float py = 1.0f, float sx = 0.0f, float sy = 0.0f, float ex = 1.0f, float ey = 1.0f); 
	// �޸�DC�� �غ��س��� �̹����� x, y ��ġ�� �׸���. 
	void draw(HDC hdc, int x, int y);
};