#include <cstdio>
#include <iostream>
#include "Stack.h"
using namespace std;


int main() {
	try {
		cout << "Start" << endl;
		{
			Stack s(100);
			int x;
			do {
				cin >> x;
				s.push(x);
			} while (x >= 0);
			cout << "s size =" << s.get_size() << endl;
			//while (s.get_size() > 0)
			cout << s.top() << endl;
			cout << "Point before copying" << endl;
			Stack foo(s);
			cout << "Point after copying" << endl;
			//Stack foo(10);
			//foo = s;
			cout << "foo size =" << foo.get_size() << endl;
			cout << foo.top() << endl;
			cout << foo.pop() << endl;
			cout << "foo size =" << foo.get_size() << endl;
			cout << "s size =" << s.get_size() << endl;
		}
		cout << "End" << endl;
		return 0;
	} catch (const std::exception &e) {
		cout << "Exception: " << e.what() << endl;
	}
}

