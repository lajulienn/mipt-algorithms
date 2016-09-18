#include <iostream>
#include "Vector2D.h"

using namespace std;

int main() {
	Vector2D foo(1, 2);
	cout << "foo = " << foo << endl;
	cout << "2 * foo = " << 2 * foo << endl;
	cout << "foo * 2 = " << foo * 2 << endl;
	cout << "foo + Vector2D(1, 1) = " << foo + Vector2D(1, 1) << endl;
	cout << "foo - Vector2D(1, 1) = " << foo - Vector2D(1, 1) << endl;
	foo += Vector2D(1, 1);
	cout << "foo += Vector2D(1, 1) = " << foo << endl;
	foo -= Vector2D(1, 1);
	cout << "foo -= Vector2D(1, 1) = " << foo << endl;
	foo *= 3;
	cout << "foo *= 3 = " << foo << endl;
	foo /= 3;
	cout << "foo /= 3 = " << foo << endl;
	cout << "foo * Vector2D(2, 3) = " << foo * Vector2D(2, 3) << endl;
	foo = Vector2D(2, 6);
	cout << "foo == (2,6) = " << (foo == Vector2D(2, 6)) << endl;
	cout << "foo != (2,6) = " << (foo != Vector2D(2, 6)) << endl;
	cout << "foo == (1,6) = " << (foo == Vector2D(1, 6)) << endl;
	cout << "foo != (1,6) = " << (foo != Vector2D(1, 6)) << endl;
	cout << Vector2D(2, 2)() << endl;

	return 0;
}