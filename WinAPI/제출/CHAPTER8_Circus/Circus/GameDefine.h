#pragma once

#include <Windows.h>
#include <math.h>
#include <vector>
#include "BitmapManager.h"
#include "CircusObject.h"

/* 윈도우 크기 */
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

#define PI 3.141592f
#define PLAYER_SPEED 500
#define MAP_WIDTH 3000

/* 이미지 리소스 */
#define IMG_BG_GROUND			L"res//back.bmp"
#define IMG_BG_ELEPHANT			L"res//back_deco.bmp"
#define IMG_BG_CROWD			L"res//back_normal.bmp"
#define IMG_BG_CROWD2			L"res//back_normal2.bmp"
#define IMG_CASH				L"res//cash.bmp"
#define IMG_GOAL				L"res//end.bmp"
#define IMG_ENEMY_ALL			L"res//enemy.bmp"
#define IMG_ENEMY_L				L"res//enemy_1b.bmp"
#define IMG_ENEMY_R				L"res//enemy_1f.bmp"
#define IMG_ENEMY_L2			L"res//enemy_b.bmp"
#define IMG_ENEMY_R2			L"res//enemy_f.bmp"
#define IMG_ENEMY_MONEY_ALL		L"res//enemy_l.bmp"
#define IMG_ENEMY_MONEY_L		L"res//enemy_l_b.bmp"
#define IMG_ENEMY_MONEY_R		L"res//enemy_l_f.bmp"
#define IMG_ENEMY_ALL2			L"res//enemy1.bmp"
#define IMG_ENEMY_JAR			L"res//front.bmp"
#define IMG_ENEMY_JAR2			L"res//front2.bmp"
#define IMG_ICON				L"res//icon.bmp"
#define IMG_METER				L"res//miter.bmp"
#define IMG_STAR1				L"res//star.bmp"
#define IMG_STAR2				L"res//star1.bmp"
#define IMG_STAR3				L"res//star2.bmp"
#define IMG_PLAYER1				L"res//player0.bmp"
#define IMG_PLAYER2				L"res//player1.bmp"
#define IMG_PLAYER3				L"res//player2.bmp"
#define IMG_PLAYER_WIN1			L"res//win.bmp"
#define IMG_PLAYER_WIN2			L"res//win2.bmp"
#define IMG_PLAYER_DIE			L"res//die.bmp"
#define IMG_TITLE				L"res//title.bmp"
#define IMG_NUMBER				L"res//number.bmp"
