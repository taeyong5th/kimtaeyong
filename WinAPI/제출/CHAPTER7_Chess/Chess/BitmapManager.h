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

	void add(Bitmap *bitmap); // 비트맵을 추가한다.
	void remove(Bitmap *bitmap); // 비트맵을 삭제한다.
	int getSize(); // 등록된 비트맵 개수를 반환한다.
	Bitmap* getBitmap(LPCWSTR fileName); // fileName의 비트맵을 반환한다.
	void draw(HDC hdc, LPCWSTR fileName, int x, int y, float px = 1.0f, float py = 1.0f); // fileName의 비트맵 파일을 그린다. x, y : 그려질 좌상위치, px, py : 원본 비트맵 너비의 px배,  높이의 py 배로 그림
};