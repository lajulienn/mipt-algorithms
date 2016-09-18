#include <cstdio>
#include <iostream>

using namespace std;

class B {
public:
	B() { cout << "B::B()\n"; };
	~B() { cout << "~B::B()\n"; };
};

class A {
public:
	A() { cout << "A::A()\n" << this << "\n"; };
	~A() { cout << "~A::A()\n"; };
	B b;
};

int main() {
	A a;
	return 0;
}