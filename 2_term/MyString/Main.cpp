#include <iostream>
#include "MyString.h"
using namespace std;

int main() {
	try {
		MyString h = "Hello", w("world");
		MyString empty; //fix this
		empty = 'c';
		cout << (h + ", " + w + '!') << endl; // Hello, world!
		const MyString c = "I am constant";
		cout << c[0] + MyString(" am good constant\n"); // I am good constant
		cout << c.get_length() << endl; // 13
		h = h;
		h += ", ";
		h += w;
		h += '! ';
		cout << h << endl; // Hello, world!
		MyString a;
		a = h = c;
		cout << a << endl; // I am constant
		a[0] = 'i';
		cout << a << endl; // i am constant
		h = "ohio";
		h.reverse();
		cout << h << endl; // oiho

		MyString z('z', 10); // создать строку из 100 букв z
		cout << z << endl;
		
		cout << "Enter your name here: ";
		cin >> h;
		cout << "Hello, " << h << endl;
		cout << "HI " + h << endl;
		cout << h << endl;

	} catch (const std::exception &e) {
		cout << "Exception: " << e.what() << endl;
	}
	return 0;
}