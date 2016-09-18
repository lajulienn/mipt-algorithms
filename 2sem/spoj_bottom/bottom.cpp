#include <iostream>
#include <vector>
#include <cstring>

using std::cin;
using std::cout;
using std::vector;
using std::endl;

vector<vector<int>> list;
vector<vector<int>> tr_list;
bool visited[5000];
int id[5000];
bool bad[5000]; // true- this component is bad
vector<int> topsort;

void dfs(int v);
void tr_dfs(int v, int id_number);

int main() {
	while (true) {
		int v, e;
		cin >> v;
		if (v == 0)
			return 0;
		cin >> e;

		list.resize(v);
		tr_list.resize(v);
		for (int i = 0; i < e; ++i) {
			int v1, v2;
			cin >> v1 >> v2;
			list[v1 - 1].push_back(v2 - 1);
			tr_list[v2 - 1].push_back(v1 - 1);
		}
		for (int i = 0; i < v; ++i) {
			if (!visited[i])
				dfs(i);
		}
		memset(visited, 0, v * sizeof(bool));
		int id_number = 0;
		for (int i = topsort.size() - 1; i >= 0; --i) {
			int x = topsort[i];
			if (!visited[x]) {
				tr_dfs(x, id_number);
				++id_number;
			}
		}
		for (int i = 0; i < v; ++i) {
			for (const auto x : list[i]) {
				if (id[x] != id[i]) {
					bad[id[i]] = true;
				}
			}
		}

		for (int i = 0; i < v; ++i) {
			if (!bad[id[i]]) {
				cout << i + 1 << " ";
			}
		}
		cout << endl;
		memset(visited, 0, v * sizeof(bool));
		memset(id, 0, v * sizeof(int));
		memset(bad, 0, v * sizeof(int));
		list.clear();
		tr_list.clear();
		topsort.clear();
	}
	return 0;
}

void dfs(int v) {
	visited[v] = 1;
	for (const auto x : list[v]) {
		if (!visited[x]) {
			dfs(x);
		}
	}
	topsort.push_back(v);
}

void tr_dfs(int v, int id_number) {
	visited[v] = 1;
	for (const auto x : tr_list[v]) {
		if (!visited[x]) {
			tr_dfs(x, id_number);
		}
	}
	id[v] = id_number;
}
