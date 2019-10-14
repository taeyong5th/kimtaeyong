#include "IntroUI.h"

void IntroUI::init(HWND hWnd)
{
	m_hWnd = hWnd;
}

void IntroUI::draw()
{
	int starCount = 0;
	int width = BitmapManager::GetInstance()->getBitmap(stars[0])->getWidth();

	while (starCount < 30)
	{
		BitmapManager::GetInstance()->prepare(stars[starCount % 3], (WINDOW_WIDTH / 2 - width * 30) + width * 2.0f * starCount, 100, 2.0f, 2.0f);
		++starCount;
	}
	starCount = 0;
	while (starCount < 30)
	{
		BitmapManager::GetInstance()->prepare(stars[starCount % 3], (WINDOW_WIDTH / 2 - width * 30) + width * 2.0f * starCount, 400, 2.0f, 2.0f);
		++starCount;
	}

	int titleWidth = BitmapManager::GetInstance()->getBitmap(IMG_TITLE)->getWidth();
	int titleHeight = BitmapManager::GetInstance()->getBitmap(IMG_TITLE)->getHeight();
	BitmapManager::GetInstance()->prepare(IMG_TITLE, WINDOW_WIDTH / 2 - titleWidth / 2, 150);

	HDC hdc = GetDC(m_hWnd);
	BitmapManager::GetInstance()->draw(hdc, 0, 0);

	//RECT rt = { 100,100,400,300 };
	//DrawText(hdc, L"테스트123", -1, &rt, DT_CENTER | DT_WORDBREAK);

	// 텍스트 출력
	static TCHAR tempstr[128];
	wsprintf(tempstr, TEXT("PRESS ENTER"));
	TextOut(hdc, WINDOW_WIDTH / 2 - 60, 500, tempstr, lstrlen(tempstr));
	ReleaseDC(m_hWnd, hdc);
}

IntroUI::IntroUI()
{
	stars[0] = IMG_STAR1;
	stars[1] = IMG_STAR2;
	stars[2] = IMG_STAR3;
	m_hWnd = nullptr;
}

IntroUI::~IntroUI()
{
}
