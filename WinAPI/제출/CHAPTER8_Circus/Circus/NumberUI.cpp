#include "NumberUI.h"

void NumberBitmap::draw(int number, int x, int y, float multiply)
{
	m_iWidth = BitmapManager::GetInstance()->getBitmap(IMG_NUMBER)->getWidth();
	m_iHeight = BitmapManager::GetInstance()->getBitmap(IMG_NUMBER)->getHeight();

	// �׸��� ������
	int arr[10];
	int arr_size = 0;

	// ���ڸ� �迭�� �������� ����
	if (number == 0)
	{
		arr[arr_size++] = 0;
	}
	while (number != 0)
	{
		arr[arr_size] = number % 10;
		number = number / 10;
		arr_size++;
	}

	// �ٽ� �������� x, y ��ġ�� �ϳ��� �׸�
	for (int i = arr_size - 1; i >= 0; --i)
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
