#include "Figure.h"

Figure::Figure(HWND hWnd, int x, int y, int width, int height) :
	hWnd(hWnd), x(x), y(y), width(width), height(height)
{
	shape = FS_ELLIPSE;
	lpRect = nullptr;
}

Figure::~Figure()
{
}

void Figure::reSize(float width, float height)
{
	this->width = width;
	this->height = height;
}

void Figure::changeShape()
{
	switch (shape)
	{
	case FS_RECT:
		this->shape = FS_ELLIPSE;
		break;
	case FS_ELLIPSE:
		this->shape = FS_RECT;
		break;
	default:
		break;
	}
}

void Figure::moveTo(float x, float y)
{
	if (lpRect == nullptr)
	{
		this->x = x;
		this->y = y;
		return;
	}
	float left = x - width / 2;
	float top = y - height / 2;
	float right = x + width / 2;
	float bottom = y + height / 2;
	if (lpRect->top < top && lpRect->bottom > bottom && lpRect->left < left && lpRect->right > right)
	{
		this->x = x;
		this->y = y;
	}
	
}

void Figure::draw()
{
	HDC hdc;
	PAINTSTRUCT ps;
	
	hdc = BeginPaint(hWnd, &ps);

	if (lpRect != nullptr)
	{
		Rectangle(hdc, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
	}

	switch (shape)
	{
	case FS_ELLIPSE:
		Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
		break;
	case FS_RECT:
		Rectangle(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
		break;
	}
	EndPaint(hWnd, &ps);
}

void Figure::setRect(const RECT* lpRect)
{
	this->lpRect = lpRect;
}
