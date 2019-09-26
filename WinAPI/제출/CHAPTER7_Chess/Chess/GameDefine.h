#pragma once

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8

#define IMG_BLACK_PAWN		L"res//block_b_00.bmp"
#define IMG_BLACK_KNIGHT	L"res//block_b_01.bmp"
#define IMG_BLACK_BISHOP	L"res//block_b_02.bmp"
#define IMG_BLACK_ROOK		L"res//block_b_03.bmp"
#define IMG_BLACK_QUEEN		L"res//block_b_04.bmp"
#define IMG_BLACK_KING		L"res//block_b_05.bmp"
							  
#define IMG_WHITE_PAWN		L"res//block_w_00.bmp"
#define IMG_WHITE_KNIGHT	L"res//block_w_01.bmp"
#define IMG_WHITE_BISHOP	L"res//block_w_02.bmp"
#define IMG_WHITE_ROOK		L"res//block_w_03.bmp"
#define IMG_WHITE_QUEEN		L"res//block_w_04.bmp"
#define IMG_WHITE_KING		L"res//block_w_05.bmp"
							 
#define IMG_BOARD_WHITE		L"res//block00.bmp"
#define IMG_BOARD_BLACK		L"res//block01.bmp"
#define IMG_BOARD_SELECTED	L"res//block02.bmp"

enum TEAM
{
	TEAM_BLACK,
	TEAM_WHITE
};

enum BOARD_POSITION_X
{
	POS_A,
	POS_B,
	POS_C,
	POS_D,
	POS_E,
	POS_F,
	POS_G,
	POS_H
};

enum BOARD_POSITION_Y
{
	POS_8,
	POS_7,
	POS_6,
	POS_5,
	POS_4,
	POS_3,
	POS_2,
	POS_1
};