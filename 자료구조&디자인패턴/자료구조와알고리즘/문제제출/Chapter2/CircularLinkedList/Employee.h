#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee
{
	char name[20]; // ���� �̸�
	int id; // ���
};

Employee* createEmployee(char name[], int id);
void printEmployee(Employee *e);