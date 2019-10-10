#include "BitmapManager.h"

BitmapManager::BitmapManager()
{
	m_MemDC = nullptr;
	m_hBitmap = nullptr;
	m_iWidth = m_iHeight = 0;
}

BitmapManager::~BitmapManager()
{
	std::map<LPCWSTR, Bitmap*>::iterator it;
	for (it = m_BitmapList.begin(); it != m_BitmapList.end(); ++it)
	{
		delete (it->second);
	}

	if (m_MemDC != nullptr)
	{
		DeleteDC(m_MemDC);
	}
}

void BitmapManager::init(HDC hdc, int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;

	if (m_MemDC == nullptr)
	{
		m_MemDC = CreateCompatibleDC(hdc);
		m_hBitmap = CreateCompatibleBitmap(hdc, width, height);
		m_oldBitmap = (HBITMAP)SelectObject(m_MemDC, m_hBitmap);
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

Bitmap* BitmapManager::getBitmap(LPCWSTR fileName)
{
	std::map<LPCWSTR, Bitmap*>::iterator it = m_BitmapList.find(fileName);

	if (it != m_BitmapList.end())
	{
		return it->second;
	}
	return nullptr;
}

bool BitmapManager::prepare(LPCWSTR fileName, int x, int y, float px, float py, float sx, float sy, float ex, float ey)
{	
	std::map<LPCWSTR, Bitmap*>::iterator it = m_BitmapList.find(fileName);

	if (it != m_BitmapList.end())
	{
		(it->second)->draw(m_MemDC, x, y, px, py, sx, sy, ex, ey);
		return true;
	}
	return false;
}

void BitmapManager::draw(HDC hdc, int x, int y)
{
	if (m_MemDC != nullptr)
	{
		BitBlt(hdc, x, y, m_iWidth, m_iHeight, m_MemDC, 0, 0, SRCCOPY);		
	}
}