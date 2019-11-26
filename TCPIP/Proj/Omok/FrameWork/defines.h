#pragma once

enum SCENE_INDEX
{
	SCENE_INDEX_TITLE,
	SCENE_INDEX_GAME,
};

enum GAME_STATE
{
	GAME_STATE_START_WAIT, // ���� ���� �� �� ���� ���� ���
	GAME_STATE_WAIT, // ���� ��ٸ��� ��
	GAME_STATE_PLAY, // ���� �÷����ϴ� ��
	GAME_STATE_OVER // ������ �����
};

enum OMOK_PLAYER_ID
{
	PLAYER_ID_NONE = -1,
	PLAYER_ID_BLACK,
	PLAYER_ID_WHITE
};

#define BOARD_WIDTH 16
#define BOARD_HEIGHT 16