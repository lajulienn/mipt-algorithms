#define _CRTDBG_MAP_ALLLOC

#include <crtdbg.h>

#include <iostream>
#include "Matrix.h"

using namespace std;

class AutoLeakChecker
{
public:
	~AutoLeakChecker() {
		_CrtDumpMemoryLeaks();
	}
} global_leak_checker;

int main() {
	//Matrix m(5, 4);
	//cout << m;
	Matrix v(10, 1); // вектор 10x1, инициализирован нулями
	for (int i = 0; i < 10; ++i)
		v(i, 0) = i;
	cout << v << endl; // [ 0 1 2 3 4 5 6 7 8 9 ]
	Matrix a(2, 3); // матрица 2x3, инициализирована нулями
	for (int i = 0; i < a.height(); ++i)
		for (int j = 0; j < a.width(); ++j)
			a(i, j) = i + 3 * j;
	cout << a << endl; // [ 0 3 6
						 // 1 4 7 ]
	const Matrix c = a;
	cout << c + 2 * a << endl; // [ 0 9 18
	// 3 12 21 ]
	cout << c(1, 1) << endl << endl; // 4
/*	try {
		a(100, 100);
	} catch (const std::exception& e) {
		cout << "Exception: " << e.what() << endl; // Exception: invalid index
	}*/
	a = Matrix(20, 10); // инициализирована нулями
/*	try {
		a += c;
	} catch (const std::exception& e) {
		cout << "Exception: " << e.what() << endl; // Exception: incompatible argument dimensions
	}*/
	a *= v; // v умножился на a справа, a = a * v
	cout << a << endl;
	v.transpose(); // v стал вектором 10x1 (транспонировался)
	cout << v << endl;
	v = a * v;
	cout << v << endl;
	Matrix a1(5, 5), a2(5, 5);
	for (int i = 0; i < 5; ++i) {
		a1(i, i) = 1;
		for (int j = 0; j < 5; ++j) {
			a2(i, j) = i + j;
		}
	}
	a1 = a1 * a2;

	cout << a1;

	cout << a.height() << "x" << a.width() << endl; // 20x1
	cout << v.height() << "x" << v.width() << endl; // 20x10


	return 0;
}