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
public:
	BitmapManager();
	~BitmapManager();

	void add(Bitmap *bitmap); // ��Ʈ���� �߰��Ѵ�.
	void remove(Bitmap *bitmap); // ��Ʈ���� �����Ѵ�.
	int getSize(); // ��ϵ� ��Ʈ�� ������ ��ȯ�Ѵ�.
	Bitmap* getBitmap(LPCWSTR fileName); // fileName�� ��Ʈ���� ��ȯ�Ѵ�.
	// �׷��� �̹����� �غ�
	void prepare(HDC hdc, LPCWSTR fileName, int x, int y, float px = 1.0f, float py = 1.0f, float sx = 0.0f, float sy = 0.0f, float ex = 1.0f, float ey = 1.0f); 
	// fileName�� ��Ʈ�� ������ �׸���. x, y : �׷��� �»���ġ, px, py : ���� ��Ʈ�� �ʺ��� px��,  ������ py ��� �׸�
	void draw(HDC hdc, int sx, int sy, int ex, int ey);
};