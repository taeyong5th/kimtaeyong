#pragma once
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
//#include <winsock.h>
#include <process.h>
#include <vector>

#define PORT_NUMBER 9000
#define MAX_CLNT 2

enum OMOK_MSG_ID
{
	MSG_GET_USERINFO,
	MSG_SET_STONE,

	MSG_UPDATE_BOARD

};

enum OMOK_PLAYER_ID
{
	PLAYER_ID_BLACK,
	PLAYER_ID_WHITE
};

struct OMOK_MSG
{
	int msgid;
	char* data;
};