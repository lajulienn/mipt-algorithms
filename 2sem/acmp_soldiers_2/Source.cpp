#include <iostream>

using std::cin;
using std::cout;

int pairs[100][100];
int N, M;

bool enter[100];
bool finished[100];

bool dfs(int x);

int main() {
	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		int h, l;
		cin >> h >> l;
		pairs[h - 1][l - 1] = 1;
	}
	for (int i = 0; i < N; ++i) {
		if (!enter[i]) {
			if (!dfs(i)) {
				cout << "No\n";
				return 0;
			}
		}
	}
	cout << "Yes\n";
	return 0;
}

bool dfs(int x) {
	enter[x] = 1;
	for (int i = 0; i < N; ++i) {
		if (pairs[x][i]) {
			if (!enter[i]) {
				if (!dfs(i))
					return false;
			} else {
				if (!finished[i])
					return false;
			}
		}
	}
	finished[x] = 1;
	return true;
}