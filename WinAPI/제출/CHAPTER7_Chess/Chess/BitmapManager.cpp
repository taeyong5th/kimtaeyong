#include "BitmapManager.h"

BitmapManager::BitmapManager()
{
	
}

BitmapManager::~BitmapManager()
{
	std::map<LPCWSTR, Bitmap*>::iterator it;
	for (it = m_BitmapList.begin(); it != m_BitmapList.end(); ++it)
	{
		delete (it->second);
	}
}

void BitmapManager::add(Bitmap *bitmap)
{
	m_BitmapList.insert(std::make_pair(bitmap->getBitmapFileName(), bitmap));
}

void BitmapManager::remove(Bitmap *bitmap)
{
	m_BitmapList.erase(bitmap->getBitmapFileName());
}

int BitmapManager::getSize()
{
	return m_BitmapList.size();
}

void BitmapManager::draw(HDC hdc, LPCWSTR fileName, int x, int y)
{
	std::map<LPCWSTR, Bitmap*>::iterator it = m_BitmapList.find(fileName);

	if (it != m_BitmapList.end())
	{	
		(it->second)->draw(hdc, x, y);
	}
	else
	{

	}
}
