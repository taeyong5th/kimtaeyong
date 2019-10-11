#include "IntroUI.h"

void IntroUI::draw(HWND hwnd)
{
	int starCount = 0;
	while (starCount < 30)
	{
		int width = BitmapManager::GetInstance()->getBitmap(stars[starCount % 3])->getWidth();
		BitmapManager::GetInstance()->prepare(stars[starCount % 3], width * 2.0f * starCount, 30, 2.0f, 2.0f);
		++starCount;
	}
	starCount = 0;
	while (starCount < 30)
	{
		int width = BitmapManager::GetInstance()->getBitmap(stars[starCount % 3])->getWidth();
		BitmapManager::GetInstance()->prepare(stars[starCount % 3], width * 2.0f * starCount, 150, 2.0f, 2.0f);
		++starCount;
	}


	RECT rt = { 100,100,400,300 };
	HDC hdc = GetDC(m_hWnd);
	DrawText(hdc, L"테스트123", -1, &rt, DT_CENTER | DT_WORDBREAK);

	// 상단 텍스트 출력
	static TCHAR tempstr[128];
	wsprintf(tempstr, TEXT("테스트456"));
	TextOut(hdc, 100, 40, tempstr, lstrlen(tempstr));

	BitmapManager::GetInstance()->draw(hdc, 0, 0);

	ReleaseDC(m_hWnd, hdc);
}

IntroUI::IntroUI()
{
	stars[0] = IMG_STAR1;
	stars[1] = IMG_STAR2;
	stars[2] = IMG_STAR3;
}

IntroUI::~IntroUI()
{
}
