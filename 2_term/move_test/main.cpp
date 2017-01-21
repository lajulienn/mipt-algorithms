#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main() {
	string a = "Hello";
	string b = "world";

	vector<string> strings;

	strings.push_back(a);
	strings.push_back(move(b));

	return 0;
}