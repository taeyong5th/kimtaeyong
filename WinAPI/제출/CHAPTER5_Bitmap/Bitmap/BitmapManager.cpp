#include "BitmapManager.h"

BitmapManager::BitmapManager()
{

}

BitmapManager::~BitmapManager()
{
	std::list<Bitmap*>::iterator it;
	for (it = m_BitmapList.begin(); it != m_BitmapList.end(); ++it)
	{
		delete (*it);
	}
}

void BitmapManager::add(Bitmap *bitmap)
{
	m_BitmapList.push_back(bitmap);
}

void BitmapManager::remove(Bitmap *bitmap)
{
	m_BitmapList.remove(bitmap);
}

int BitmapManager::getSize()
{
	return m_BitmapList.size();
}

void BitmapManager::draw(HDC hdc)
{
	std::list<Bitmap*>::iterator it;
	
	for (it = m_BitmapList.begin(); it != m_BitmapList.end() ; ++it)
	{
		(*it)->draw(hdc);
	}
}

void BitmapManager::runClickEvent(HWND hwnd, int x, int y)
{
	std::list<Bitmap*>::reverse_iterator it;

	for (it = m_BitmapList.rbegin(); it != m_BitmapList.rend(); ++it)
	{
		// x, y Ŭ���� ���� �ִ� �̹��� �� ���� ���� �׷��� �̹����� �̺�Ʈ �Լ��� ȣ���Ѵ�.
		if ((*it)->isVaildRange(x, y))
		{
			(*it)->runClickEvent(hwnd, x, y);
			break;
		}
	}
}
