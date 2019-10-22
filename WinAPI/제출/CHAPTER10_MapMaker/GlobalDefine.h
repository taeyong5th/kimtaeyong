#pragma once

#include <iostream>
#include <string>
#include <conio.h>
#include <iomanip>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include "BitmapManager.h"

#define MAP_WIDTH_MIN 13
#define MAP_HEIGHT_MIN 13
#define MAP_WIDTH_MAX 30
#define MAP_HEIGHT_MAX 30
#define WINDOW_WIDTH 530
#define WINDOW_HEIGHT 460

/* 이미지 리소스 */
#define IMG_BG				 L"res//back.bmp"

#define IMG_BLOCK_BLANK			 TEXT("res//block_blank.bmp")
#define IMG_BLOCK_A				 TEXT("res//block00.bmp")
#define IMG_BLOCK_U				 TEXT("res//block01.bmp")
#define IMG_BLOCK_L				 TEXT("res//block02.bmp")
#define IMG_BLOCK_D				 TEXT("res//block03.bmp")
#define IMG_BLOCK_R				 TEXT("res//block04.bmp")
#define IMG_BLOCK_GRAY			 TEXT("res//block05.bmp")
#define IMG_BLOCK_FOREST		 TEXT("res//block06.bmp")
#define IMG_BLOCK_WATER			 TEXT("res//block07.bmp")
#define IMG_BLOCK_A_HARD		 TEXT("res//block08.bmp")
#define IMG_BLOCK_U_HARD		 TEXT("res//block09.bmp")
#define IMG_BLOCK_L_HARD		 TEXT("res//block10.bmp")
#define IMG_BLOCK_D_HARD		 TEXT("res//block11.bmp")
#define IMG_BLOCK_R_HARD		 TEXT("res//block12.bmp")
#define IMG_BLOCK_MARK			 TEXT("res//block13.bmp")
#define IMG_BLOCK_FLAG			 TEXT("res//block14.bmp")

#define IMG_ENEMY_TANK_D0			 TEXT("res//e_down_00.bmp")
#define IMG_ENEMY_TANK_D1			 TEXT("res//e_down_01.bmp")
#define IMG_ENEMY_TANK_L0			 TEXT("res//e_left_00.bmp")
#define IMG_ENEMY_TANK_L1			 TEXT("res//e_left_01.bmp")
#define IMG_ENEMY_TANK_U0			 TEXT("res//e_up_00.bmp")
#define IMG_ENEMY_TANK_U1			 TEXT("res//e_up_01.bmp")
#define IMG_ENEMY_TANK_R0			 TEXT("res//e_right_00.bmp")
#define IMG_ENEMY_TANK_R1			 TEXT("res//e_right_01.bmp")

#define IMG_PLAYER_TANK_D0			 TEXT("res//tank_down_00.bmp")
#define IMG_PLAYER_TANK_D1			 TEXT("res//tank_down_01.bmp")
#define IMG_PLAYER_TANK_L0			 TEXT("res//tank_left_00.bmp")
#define IMG_PLAYER_TANK_L1			 TEXT("res//tank_left_01.bmp")
#define IMG_PLAYER_TANK_U0			 TEXT("res//tank_up_00.bmp")
#define IMG_PLAYER_TANK_U1			 TEXT("res//tank_up_01.bmp")
#define IMG_PLAYER_TANK_R0			 TEXT("res//tank_right_00.bmp")
#define IMG_PLAYER_TANK_R1			 TEXT("res//tank_right_01.bmp")

#define IMG_SHIELD_0			 TEXT("res//shield_00.bmp")
#define IMG_SHIELD_1			 TEXT("res//shield_01.bmp")

#define IMG_EXPLOSION_0			 TEXT("res//explosion_00.bmp")
#define IMG_EXPLOSION_1			 TEXT("res//explosion_01.bmp")
#define IMG_EXPLOSION_2			 TEXT("res//explosion_02.bmp")
#define IMG_EXPLOSION_3			 TEXT("res//explosion_03.bmp")
#define IMG_EXPLOSION_4			 TEXT("res//explosion_04.bmp")

#define IMG_ICON_PLAYER			 TEXT("res//player_icon.bmp")
#define IMG_ICON_ENEMY			 TEXT("res//enemy_icon.bmp")
#define IMG_ICON_STAGE			 TEXT("res//stage_icon.bmp")