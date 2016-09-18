#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct point {
	int x;
	int y;
};

int N;
point start;
point finish;
vector<string> picture; //our playground
int distances[40][40]; // (distances - 1) from current square to start square
bool field[40][40]; // true - square is free, false - there's a ball here

void BFS();
void DrawPath();

int main() {

	cin >> N;

	for (int i = 0; i < N; ++i) {
		string line;
		cin >> line;
		picture.push_back(line);

		for (int j = 0; j < N; ++j) {
			if (picture[i][j] == '.') {
				field[i][j] = true;
			} else if (picture[i][j] == 'O') {
				field[i][j] = false;
			} else if (picture[i][j] == '@') {
				field[i][j] = true;
				start.x = i;
				start.y = j;
			} else if (picture[i][j] == 'X') {
				field[i][j] = true;
				finish.x = i;
				finish.y = j;
			}
		}
	}

	BFS();

	if (!distances[finish.x][finish.y]) {
		cout << "No" << endl;;
		return 0;
	}

	cout << "Yes" << endl;

	DrawPath();

	return 0;
}

void BFS() {
	queue<point> q;
	q.push(start);
	distances[start.x][start.y] = 1;

	while (!q.empty()) {
		point current = q.front();
		point next;
		q.pop();
		for (int i = 0; i < 4; ++i) {
			switch (i) {
			case 0:
				next.x = current.x + 1;
				next.y = current.y;
				break;
			case 1:
				next.x = current.x - 1;
				next.y = current.y;
				break;
			case 2:
				next.x = current.x;
				next.y = current.y + 1;
				break;
			case 3:
				next.x = current.x;
				next.y = current.y - 1;
				break;
			}

			if (next.x >= 0 && next.y >= 0 && next.x < N && next. y < N 
						&& !distances[next.x][next.y] && field[next.x][next.y]) {
				distances[next.x][next.y] = distances[current.x][current.y] + 1;
				q.push(next);
			}

			if (next.x == finish.x && next.y == finish.y)
				return;
		}
	}
}

void DrawPath() {
	int steps = distances[finish.x][finish.y] - 1;
	point current = finish;
	picture[finish.x][finish.y] = '+';

	for (int i = steps; i > 1; --i) {
		point next;
		for (int i = 0; i < 4; ++i) {
			switch (i) {
			case 0:
				next.x = current.x + 1;
				next.y = current.y;
				break;
			case 1:
				next.x = current.x - 1;
				next.y = current.y;
				break;
			case 2:
				next.x = current.x;
				next.y = current.y + 1;
				break;
			case 3:
				next.x = current.x;
				next.y = current.y - 1;
				break;
			}
			if (distances[next.x][next.y] == distances[current.x][current.y] - 1) {
				picture[next.x][next.y] = '+';
				current = next;
				break;
			}
		}
	}

	// display result
	for (int i = 0; i < N; ++i) {
		string line = picture[i];
		cout << line << endl; 
	}
}