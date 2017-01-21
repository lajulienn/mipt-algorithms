#include <iostream>
#include <string>
#include <queue>

using namespace std;

int num_str, num_smb;

int count_comps(bool *garden, bool *marked);
void bfs(int x, bool *garden, bool *marked);

int main() {

	cin >> num_str >> num_smb;

	string row;
	bool *garden = new bool[num_str * num_smb];
	bool *marked = new bool[num_str * num_smb];

	for (int i = 0; i < num_str; ++i) {
		cin >> row;
		for (int j = 0; j < num_smb; ++j) {
			garden[i * num_smb + j] = row[j] != '.';
			marked[i * num_smb + j] = 0;
		}
	}

	cout << count_comps(garden, marked) << endl;
	delete[] garden;
	delete[] marked;
	
	return 0;
}

int count_comps(bool *garden, bool *marked) {
	int count = 0;
	for (int x = 0; x < num_str * num_smb; ++x) { // x - index of element
		if (marked[x] || !garden[x])
			continue;
		bfs(x, garden, marked);
		++count;
	}
	return count;
}

void bfs(int x, bool *garden, bool *marked) {
	std::queue<int> q;
	q.push(x);
	marked[x] = 1;
	while (!q.empty()) {
		int next;
		int current = q.front(); // index of current element
		q.pop();
		for (int i = 0; i < 4; ++i) {
			switch (i) {
			case 0:
				next = current - 1;
				if (next / num_smb != current / num_smb)
					next = -1;
				break;
			case 1:
				next = current + 1;
				if (next / num_smb != current / num_smb)
					next = -1;
				break;
			case 2:
				next = current - num_smb;
				break;
			case 3:
				next = current + num_smb;
				if (next > num_str * num_smb)
					next = -1;
				break;
			}
			if (next < 0 || marked[next] || !garden[next])
				continue;

			marked[next] = 1;
			q.push(next);
		}
	}
}