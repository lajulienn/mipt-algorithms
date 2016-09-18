#include <iostream>
#include <queue>

using namespace std;

int N;
int matrix[100][100];
int marked[100];
const int START = 0;

bool BFS(int start);
bool isConnected();

int main() {

	cin >> N;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j)
			cin >> matrix[i][j];
	}

	if (BFS(START) && isConnected()) {
		cout << "YES" << endl;
		return 0;
	}

	cout << "NO" << endl;

	return 0;
}

bool BFS(int start) {
	std::queue<int> q;
	q.push(start);
	marked[start] = 1;
	int current = 0;

	while (!q.empty()) {
		current = q.front();
		q.pop();

		for (int next = 0; next < N; ++next) {
			if (matrix[current][next]) {
				if (marked[next] == 0) {
					matrix[current][next] = 0;
					matrix[next][current] = 0;
					marked[next] = 1;
					q.push(next);
				} else if (marked[next] == 1) {
					return false;
				}
			}
		}
	}
	return true;
}

bool isConnected() {
	for (int i = 0; i < N; ++i) {
		if (!marked[i]) {
			return false;
		}
	}
	return true;
}