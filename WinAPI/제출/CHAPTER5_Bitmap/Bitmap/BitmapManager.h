#pragma once
#include "Bitmap.h"
#include <vector>

class BitmapManager
{
private:
	std::vector<Bitmap> m_Bitmaps;

public:
	BitmapManager();
	~BitmapManager();

	void push();

};