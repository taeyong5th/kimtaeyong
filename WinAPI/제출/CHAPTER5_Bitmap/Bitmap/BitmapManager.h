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

	void add(Bitmap *bitmap); // 비트맵을 추가한다.
	void remove(Bitmap *bitmap); // 비트맵을 삭제한다.
	int getSize(); // 등록된 비트맵 개수를 반환한다.
	void draw(HDC hdc); // 비트맵 리스트에 저장된 이미지를 모두 그린다.
	void runClickEvent(HWND hwnd, int x, int y); // x, y 좌표 최상단에 있는 비트맵 이미지의 이벤트함수를 호출한다.
};