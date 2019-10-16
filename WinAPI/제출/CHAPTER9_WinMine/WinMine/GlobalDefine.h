#pragma once

#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include "BitmapManager.h"

#define WIDTH 20
#define HEIGHT 16

#define MINE -1
#define MINE_COUNT 25

/* 이미지 리소스 */
#define IMG_BLOCK			 L"res//block.bmp"
#define IMG_BLOCK_0			 L"res//block_0.bmp"
#define IMG_BLOCK_1			 L"res//block_1.bmp"
#define IMG_BLOCK_2			 L"res//block_2.bmp"
#define IMG_BLOCK_3			 L"res//block_3.bmp"
#define IMG_BLOCK_4			 L"res//block_4.bmp"
#define IMG_BLOCK_5			 L"res//block_5.bmp"
#define IMG_BLOCK_6			 L"res//block_6.bmp"
#define IMG_BLOCK_7			 L"res//block_7.bmp"
#define IMG_BLOCK_8			 L"res//block_8.bmp"
#define IMG_FLAG			 L"res//flag.bmp"
#define IMG_MINE			 L"res//mine.bmp"
#define IMG_BG				 L"res//back.bmp"

enum KEY
{
	KEY_LEFT = 'a',
	KEY_RIGHT = 'd',
	KEY_UP = 'w',
	KEY_DOWN = 's',
	KEY_ESC = 27,
	KEY_ENTER = 13,
	KEY_FLAG = '.'
};