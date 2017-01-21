#include <cstdio>
#include <iostream>
#include <queue>

using std::cin;
using std::cout;
using std::endl;

int N;
int g[100][100];
int marked[100];
int start, finish;

void bfs(int i);

int main() {
	freopen("input.txt", "r", stdin);
	cin >> N;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> g[i][j];
		}
	}
	cin >> start >> finish;
	bfs(start - 1);
	cout << marked[finish - 1] - 1;
	return 0;
}

void bfs(int i) {
	std::queue<int> q;
	q.push(i);
	marked[i] = 1;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int j = 0; j < N; ++j) {
			if (g[v][j]){
				if (!marked[j]) {
					marked[j] = marked[v] + 1;
					q.push(j);
				}
			}
		}
	}
}