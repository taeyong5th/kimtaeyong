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
		// x, y 클릭된 곳에 있는 이미지 중 가장 위에 그려진 이미지의 이벤트 함수만 호출한다.
		if ((*it)->isVaildRange(x, y))
		{
			(*it)->runClickEvent(hwnd, x, y);
			break;
		}
	}
}
