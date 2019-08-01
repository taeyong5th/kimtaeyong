#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

//Exam_1
//void main()
//{
//	vector<int> v;
//	v.push_back(10);
//	v.push_back(20);
//	v.push_back(30);
//	v.push_back(40);
//	v.push_back(50);
//
//	cout << "v: ";
//	for (vector<int>::size_type i = 0; i < v.size(); ++i)
//		cout << v[i] << " ";
//	cout << endl;
//
//	cout << accumulate(v.begin(), v.end(), 0) << endl;
//	cout << accumulate(v.begin(), v.end(), 100) << endl;
//}

//Exam_2
//template <typename T>
//struct Plus
//{
//	T operator()(const T& left, const T& right)
//	{
//		return left + right;
//	}
//};
//
//void main()
//{
//	vector<int> v;
//	v.push_back(1);
//	v.push_back(2);
//	v.push_back(3);
//	v.push_back(4);
//	v.push_back(5);
//
//	cout << "v: ";
//	for (vector<int>::size_type i = 0; i < v.size(); ++i)
//		cout << v[i] << " ";
//	cout << endl;
//
//	// 사용자 합 연산 0+1+2+3+4+5
//	cout << accumulate(v.begin(), v.end(), 0, Plus<int>()) << endl;
//	// plus 합 연산 0+1+2+3+4+5
//	cout << accumulate(v.begin(), v.end(), 0, plus<int>()) << endl;
//	// multiplies 곱 연산 1*1*2*3*4*5
//	cout << accumulate(v.begin(), v.end(), 1, multiplies<int>()) << endl;
//}

//Exam_3
//void main()
//{
//	vector<int> v1;
//	v1.push_back(1);
//	v1.push_back(2);
//	v1.push_back(3);
//	v1.push_back(4);
//	v1.push_back(5);
//
//	vector<int> v2;
//	v2.push_back(2);
//	v2.push_back(2);
//	v2.push_back(2);
//	v2.push_back(2);
//	v2.push_back(2);
//
//	// 0 + 1*2 + 2*2 + 3*2 + 4*2 + 5*2
//	cout << inner_product(v1.begin(), v1.end(), v2.begin(), 0) << endl;
//	// 100 + 1*2 + 2*2 + 3*2 + 4*2 + 5*2
//	cout << inner_product(v1.begin(), v1.end(), v2.begin(), 100) << endl;
//}

//Exam_4
//int Plus(int left, int right)
//{
//	return left + right;
//}
//
//int Minus(int left, int right)
//{
//	return left - right;
//}
//
//void main()
//{
//	vector<int> v1;
//	v1.push_back(10);
//	v1.push_back(20);
//	v1.push_back(30);
//	v1.push_back(40);
//	v1.push_back(50);
//
//	vector<int> v2;
//	v2.push_back(2);
//	v2.push_back(2);
//	v2.push_back(2);
//	v2.push_back(2);
//	v2.push_back(2);
//
//	// 0 + 10-2 + 20-2 + 30-2 + 40-2 + 50-2 사용자 함수 사용
//	cout << inner_product(v1.begin(), v1.end(), v2.begin(), 0, Plus, Minus) << endl;
//	// 0 + 10-2 + 20-2 + 30-2 + 40-2 + 50-2 STL 함수자 사용
//	cout << inner_product(v1.begin(), v1.end(), v2.begin(), 0, plus<int>(), minus<int>()) << endl;
//}

//Exam_5
//void main()
//{
//	vector<int> v1;
//	v1.push_back(10);
//	v1.push_back(20);
//	v1.push_back(30);
//	v1.push_back(40);
//	v1.push_back(50);
//
//	cout << "v1: ";
//	for (vector<int>::size_type i = 0; i < v1.size(); ++i)
//		cout << v1[i] << " ";
//	cout << endl;
//
//	vector<int> v2(5); //size: 5인 vector 생성
//	vector<int>::iterator iter_end;
//	iter_end = adjacent_difference(v1.begin(), v1.end(), v2.begin());
//
//	cout << "v2: ";
//	for (vector<int>::size_type i = 0; i < v2.size(); ++i)
//		cout << v2[i] << " ";
//	cout << endl;
//}

//Exam_6
//int Plus(int left, int right)
//{
//	return left + right;
//}
//
//void main()
//{
//	vector<int> v1;
//	v1.push_back(10);
//	v1.push_back(20);
//	v1.push_back(30);
//	v1.push_back(40);
//	v1.push_back(50);
//
//	cout << "v1: ";
//	for (vector<int>::size_type i = 0; i < v1.size(); ++i)
//		cout << v1[i] << " ";
//	cout << endl;
//
//	vector<int> v2(5); //size: 5인 vector 생성
//	vector<int>::iterator iter_end;
//	//iter_end = adjacent_difference(v1.begin(), v1.end(), v2.begin(), plus<int>());
//	iter_end = adjacent_difference(v1.begin(), v1.end(), v2.begin(), Plus);
//
//	cout << "v2: ";
//	for (vector<int>::size_type i = 0; i < v2.size(); ++i)
//		cout << v2[i] << " ";
//	cout << endl;
//}

//Exam_7
//void main()
//{
//	vector<int> v1;
//	v1.push_back(10);
//	v1.push_back(20);
//	v1.push_back(30);
//	v1.push_back(40);
//	v1.push_back(50);
//
//	cout << "v1: ";
//	for (vector<int>::size_type i = 0; i < v1.size(); ++i)
//		cout << v1[i] << " ";
//	cout << endl;
//
//	vector<int> v2(5); //size: 5인 vector 생성
//	vector<int>::iterator iter_end;
//	iter_end = partial_sum(v1.begin(), v1.end(), v2.begin());
//
//	cout << "v2: ";
//	for (vector<int>::size_type i = 0; i < v2.size(); ++i)
//		cout << v2[i] << " ";
//	cout << endl;
//}

//Exam_8
int Multi(int left, int right)
{
	return left * right;
}

void main()
{
	vector<int> v1;
	v1.push_back(10);
	v1.push_back(20);
	v1.push_back(30);
	v1.push_back(40);
	v1.push_back(50);

	cout << "v1: ";
	for (vector<int>::size_type i = 0; i < v1.size(); ++i)
		cout << v1[i] << " ";
	cout << endl;

	vector<int> v2(5); //size: 5인 vector 생성
	vector<int>::iterator iter_end;
	//iter_end = partial_sum(v1.begin(), v1.end(), v2.begin(), multiplies<int>());
	iter_end = partial_sum(v1.begin(), v1.end(), v2.begin(), Multi);

	cout << "v2: ";
	for (vector<int>::size_type i = 0; i < v2.size(); ++i)
		cout << v2[i] << " ";
	cout << endl;
}