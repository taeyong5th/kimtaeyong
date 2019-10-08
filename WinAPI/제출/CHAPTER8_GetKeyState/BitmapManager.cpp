#include "BitmapManager.h"

BitmapManager::BitmapManager()
{
	m_MemDC = nullptr;
}

BitmapManager::~BitmapManager()
{
	std::map<LPCWSTR, Bitmap*>::iterator it;
	for (it = m_BitmapList.begin(); it != m_BitmapList.end(); ++it)
	{
		delete (it->second);
	}

	DeleteDC(m_MemDC);
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

Bitmap* BitmapManager::getBitmap(LPCWSTR fileName)
{
	std::map<LPCWSTR, Bitmap*>::iterator it = m_BitmapList.find(fileName);

	if (it != m_BitmapList.end())
	{
		return it->second;
	}
	return nullptr;
}

void BitmapManager::prepare(HDC hdc, LPCWSTR fileName, int x, int y, float px, float py, float sx, float sy, float ex, float ey)
{
	if (m_MemDC == nullptr)
	{
		m_MemDC = CreateCompatibleDC(hdc);
		m_hBitmap = CreateCompatibleBitmap(hdc, 1024, 1000);
		SelectObject(m_MemDC, m_hBitmap);
	}

	std::map<LPCWSTR, Bitmap*>::iterator it = m_BitmapList.find(fileName);

	if (it != m_BitmapList.end())
	{
		(it->second)->prepare(m_MemDC, x, y, px, py, sx, sy, ex, ey);
	}
}

void BitmapManager::draw(HDC hdc, int sx, int sy, int ex, int ey)
{
	if (m_MemDC != nullptr)
	{
		BitBlt(hdc, sx, sy, ex, ey, m_MemDC, 0, 0, SRCCOPY);
	}
}