#pragma once

#include<iostream>
#include<string>
#include<conio.h>
#include<iomanip>
#include<Windows.h>
#include <stdlib.h>
#include <time.h>


using namespace std;

#define WIDTH 16
#define HEIGHT 16

#define MINE -1
#define MINE_COUNT 25

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