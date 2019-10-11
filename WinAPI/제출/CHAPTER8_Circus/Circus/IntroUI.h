#pragma once
#include "GameDefine.h"

class IntroUI
{
private:
	HWND m_hWnd;
	LPCWSTR stars[3];

public:
	void draw(HWND hwnd);
	IntroUI();
	~IntroUI();
};