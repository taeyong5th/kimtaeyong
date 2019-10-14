#pragma once
#include "GameDefine.h"

class IntroUI
{
private:
	HWND m_hWnd;
	LPCWSTR stars[3];

public:
	void init(HWND hWnd);
	void draw();
	IntroUI();
	~IntroUI();
};