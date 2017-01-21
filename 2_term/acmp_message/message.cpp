#include <iostream>
#include <stack>

using namespace std;

char data[100];
int size = 0;
int number = 0;

void dfs(int *digits, bool *marked);


int main() {
	cin >> data;

	// determining length of sequence of digits
	for (auto x : data) {
		if (x == '\0')
			break;
		++size;
	}

	int *digits = new int[size];
	bool *marked = new bool[size];

	// convertation array of char to array of int and initializing marked
	for (int i = 0; i < size; ++i) {
		digits[i] = data[i] - '0';
		marked[i] = 0;
	}

	dfs(digits, marked);

	cout << number << endl;
	
	return 0;
}

void dfs(int *digits, bool *marked) {
	marked[0] = 1;

	stack<int> s;
	s.push(0);
	while (!s.empty()) {
		int current = s.top();
		s.pop();
		if (current == size ) {
			++number;
			continue;
		}
		if (current < size - 1 && digits[current] != 0) {
			int next = 10 * digits[current] + digits[current + 1];
			if (next <= 33)
				s.push(current + 2);
		}
		s.push(current + 1);
	}
}