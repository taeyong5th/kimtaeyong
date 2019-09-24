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
	void draw(HDC hdc, int bitmapID, int x, int y); // id가 bitmapID인 비트맵을 그린다.	
};