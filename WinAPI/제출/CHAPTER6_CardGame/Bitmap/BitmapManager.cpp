#include "BitmapManager.h"

BitmapManager::BitmapManager()
{
	
}

BitmapManager::~BitmapManager()
{
	std::map<int, Bitmap*>::iterator it;
	for (it = m_BitmapList.begin(); it != m_BitmapList.end(); ++it)
	{
		delete (it->second);
	}
}

void BitmapManager::add(Bitmap *bitmap)
{
	m_BitmapList.insert(std::make_pair(bitmap->getBitmapID(), bitmap));
}

void BitmapManager::remove(Bitmap *bitmap)
{
	m_BitmapList.erase(bitmap->getBitmapID());
}

int BitmapManager::getSize()
{
	return m_BitmapList.size();
}

void BitmapManager::draw(HDC hdc, int bitmapID, int x, int y)
{
	std::map<int, Bitmap*>::iterator it = m_BitmapList.find(bitmapID);

	if (it != m_BitmapList.end())
	{	
		(it->second)->setPosition(x, y);
		(it->second)->draw(hdc);
	}
}
