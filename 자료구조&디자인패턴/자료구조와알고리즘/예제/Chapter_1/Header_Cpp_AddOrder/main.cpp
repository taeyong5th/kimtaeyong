#include <iostream>
#include "Point.h"
#include "Distance.h"
using namespace std;

void main()
{
	Point a = { 0, 0 };
	Point b = { 3, 4 };

	double dist_a_b = Distance(a, b);

	cout << "(" << a.x << ", " << a.y << ") 와 ";
	cout << "(" << b.x << ", " << b.y << ") 의 거리 = " << dist_a_b << endl;

	return;
}