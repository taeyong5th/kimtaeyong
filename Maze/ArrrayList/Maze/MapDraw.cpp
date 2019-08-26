#include "MapDraw.h"


MapDraw::MapDraw()
{

}

void MapDraw::ErasePoint(int x, int y)
{
	gotoxy(x*2, y);
	cout << "  ";
	gotoxy(-1, -1);
	return;
}

void MapDraw::DrawPoint(string str, int x, int y)
{
	gotoxy(x*2, y);
	cout << str;
	gotoxy(-1,-1);
	return;
}

void MapDraw::DrawMidText(string str, int x, int y)
{
	if (x > str.size() / 2)
		x -= str.size() / 2;
	gotoxy(x, y);
	cout << str;
	return;
}
void MapDraw::TextDraw(string str, int x, int y)
{
	gotoxy(x, y);
	cout << str;
}


void MapDraw::BoxDraw(int Start_x, int Start_y, int Width, int Height, bool isClear)
{
	for (int y = 0; y < Height; y++)
	{
		gotoxy(Start_x, Start_y+y);
		if (y == 0)
		{
			for (int x = 0; x < Width; x++)
			{
				cout << "¢Æ";
			}			
		}
		else if (y == Height - 1)
		{
			for (int x = 0; x < Width; x++)
			{
				cout << "¢Æ";
			}
		}
		else
		{
			if (isClear)
			{
				cout << "¢Æ";
				for (int x = 1; x < Width - 1; x++)
				{
					cout << "  ";
				}
				cout << "¢Æ";
			}
			else
			{
				cout << "¢Æ";
				gotoxy(Start_x + (Width - 1) * 2, Start_y + y);
				cout << "¢Æ";
			}
		}
	}
	return;
}

MapDraw::~MapDraw()
{
}
