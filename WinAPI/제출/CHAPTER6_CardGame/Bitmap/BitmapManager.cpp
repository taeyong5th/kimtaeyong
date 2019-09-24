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

void BitmapManager::draw(HDC hdc, int bitmapID, int x, int y)
{
	std::list<Bitmap*>::iterator it;

	for (it = m_BitmapList.begin(); it != m_BitmapList.end(); ++it)
	{
		if ((*it)->getBitmapID() == bitmapID)
		{
			(*it)->setPosition(x, y);
			(*it)->draw(hdc);
			break;
		}
	}
}
