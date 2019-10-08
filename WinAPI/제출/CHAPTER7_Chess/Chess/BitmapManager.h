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
	HBITMAP m_hBitmap; // 비트맵 정보
public:
	BitmapManager();
	~BitmapManager();

	void add(Bitmap *bitmap); // 비트맵을 추가한다.
	void remove(Bitmap *bitmap); // 비트맵을 삭제한다.
	int getSize(); // 등록된 비트맵 개수를 반환한다.
	Bitmap* getBitmap(LPCWSTR fileName); // fileName의 비트맵을 반환한다.
	// 그려질 이미지를 준비
	void prepare(HDC hdc, LPCWSTR fileName, int x, int y, float px = 1.0f, float py = 1.0f, float sx = 0.0f, float sy = 0.0f, float ex = 1.0f, float ey = 1.0f); 
	// fileName의 비트맵 파일을 그린다. x, y : 그려질 좌상위치, px, py : 원본 비트맵 너비의 px배,  높이의 py 배로 그림
	void draw(HDC hdc, int sx, int sy, int ex, int ey);
};