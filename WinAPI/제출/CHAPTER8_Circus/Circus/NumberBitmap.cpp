#include "NumberBitmap.h"

void NumberBitmap::draw(UINT number, int x, int y, float multiply, UINT digits)
{
	number = number < 999999 ? number : 999999;
	digits = digits < 6 ? digits : 6;

	m_iWidth = BitmapManager::GetInstance()->getBitmap(IMG_NUMBER)->getWidth();
	m_iHeight = BitmapManager::GetInstance()->getBitmap(IMG_NUMBER)->getHeight();

	// 그리기 설정값
	int arr[6] = {0, 0, 0, 0, 0, 0};
	int arr_size = 0;

	while (number != 0)
	{
		arr[arr_size] = number % 10;
		number = number / 10;
		arr_size++;
	}

	// 다시 역순으로 x, y 위치에 하나씩 그림
	for (int i = digits - 1; i >= 0; --i)
	{
		BitmapManager::GetInstance()->prepare(IMG_NUMBER, x, y, multiply, multiply, 0.1f * arr[i], 0.0f, 0.1f * (arr[i] + 1), 1.0f);
		x += m_iWidth / 10 * multiply;
	}

}

NumberBitmap::NumberBitmap()
{
	m_ix = 0;
	m_iy = 0;
}

NumberBitmap::~NumberBitmap()
{
}
