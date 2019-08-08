#include "Employee.h"

Employee * createEmployee(char name[], int id)
{
	Employee* newEmployee = (Employee*)malloc(sizeof(Employee));
	strcpy_s(newEmployee->name, name);
	newEmployee->id = id;

	return newEmployee;
}

void printEmployee(Employee * e)
{
	printf("id : %d , name : %s\n", e->id, e->name);
}
