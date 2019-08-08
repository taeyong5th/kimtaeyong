#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee
{
	char name[20]; // 직원 이름
	int id; // 사번
};

Employee* createEmployee(char name[], int id);
void printEmployee(Employee *e);