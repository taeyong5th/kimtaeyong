#pragma once

#define MAP_SIZE_WIDTH 45
#define MAP_SIZE_HEIGHT 30

#define WINDOW_SIZE_WIDTH (MAP_SIZE_WIDTH * 2)
#define WINDOW_SIZE_HEIGHT (MAP_SIZE_HEIGHT + 3)

#define SNAKE_DEFAULT_SPEED 200 // �� �⺻ �ӵ�
#define SNAKE_DEFAULT_SPEED_UP_INTERVAL 10 // ���� ������ ���� ������ �ӵ�
#define SNAKE_DEFAULT_SPEED_MAX 50 // �� �ִ� �ӵ�

#define SNAKE_CREATE_FOOD_INTERVAL 1000 // ���� ������ �ð� ����

#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'
#define KEY_UP 'w'
#define KEY_DOWN 's'

#define FOOD_MAX 10 // ���� �ִ� ����
#define WALL_COUNT 50 // �� ����