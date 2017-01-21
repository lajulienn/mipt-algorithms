#include <iostream>
#include <queue>
#include <utility>

using namespace std;

int N;
pair<int, int> start;
pair<int, int> finish;
int marked[20][20];

void bfs(pair<int, int> start);

int main() {
	cin >> N >> start.first >> start.second >> finish.first >> finish.second;
	--start.first;
	--start.second;
	--finish.first;
	--finish.second;

	bfs(start);
	int result = marked[finish.first][finish.second] - 1;
	if (result == -1)
		return 0;
	cout << result << endl;
	return 0;
}

void bfs(pair<int, int> start) {
	queue<pair<int, int>> q;
	q.push(start);
	marked[start.first][start.second] = 1;
	while (!q.empty()) {
		pair<int, int> current = q.front();

		// go through all neigbours of current
		int x = current.first;
		int y = current.second;
		pair<int, int> next;
		
		for (int i = 0; i < 8; ++i) {
			switch (i) {
			case 0:
				next.first = x + 1;
				next.second = y + 2;
				break;
			case 1:
				next.first = x + 1;
				next.second = y - 2;
				break;
			case 2:
				next.first = x - 1;
				next.second = y + 2;
				break;
			case 3:
				next.first = x - 1;
				next.second = y - 2;
				break;
			case 4:
				next.first = x + 2;
				next.second  = y + 1;
				break;
			case 5:
				next.first = x + 2;
				next.second = y - 1;
				break;
			case 6:
				next.first = x - 2;
				next.second = y + 1;
				break;
			case 7:
				next.first = x - 2;
				next.second = y - 1;
				break;
			}
			if (next.first < 0 || next.second  < 0 || next.first >= N || next.second  >= N) {
				continue;
			}
			if (!marked[next.first][next.second]) {
				marked[next.first][next.second] = marked[x][y] + 1;
				q.push(next);
			}
		}
		q.pop();
	}
}