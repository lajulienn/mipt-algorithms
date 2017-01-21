#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

vector<vector<int>> list; // adjacency list of original graph
vector<vector<int>> tr_list; //  -||- transposed graph
vector<vector<int>> components; // strongly connected components
vector<int> topsort; // reversed topsort
bool *visited;
//int **list;
//int **tr_list;

void dfs(int v);
void tr_dfs(int v, int comp_number);

int main() {
	int v, e;
	scanf("%d%d", &v, &e);
	if (v == 0)
		return 0;

	list.resize(v);
	tr_list.resize(v);
	visited = new bool[v];
	/*list = new int*[v];
	tr_list = new int*[v];*/
	memset(visited, 0, v * sizeof(bool));

	for (int i = 0; i < e; ++i) {
		//list.push_back(vector<int>());
		//tr_list.push_back(vector<int>());

		int v1, v2;
		scanf("%d%d", &v1, &v2);
		list[v1 - 1].push_back(v2 - 1);
		tr_list[v2 - 1].push_back(v1 - 1);
	}
	for (int i = 0; i < v; ++i) {
		if (!visited[i])
			dfs(i);
	}
	memset(visited, 0, v * sizeof(bool));

	int comp_number = 0;
	for (int i = topsort.size() - 1; i >= 0; --i) {
		int x = topsort[i];
		if (!visited[x]) {
			components.push_back(vector<int>());
			tr_dfs(x, comp_number);
			++comp_number;
		}
	}
	memset(visited, 0, v * sizeof(bool));
	int candidate = components.size() - 1; // number of the last component
	if (candidate == -1) {
		cout << 0;
		return 0;
	}
	tr_dfs(components[candidate].back(), -1);
	for (int i = 0; i < v; ++i) { //check if our component is suitable
		if (!visited[i]) {
			cout << 0; // our component isn't reachable from all the vertices
			return 0;
		}
	}
	int count_ = components[candidate].size();
	//cout << count_ << endl; // number of members of the good component
	printf("%d\n", count_);
	sort(components[candidate].begin(), components[candidate].end());
	for (int i = 0; i < count_; ++i) {
		printf("%d ", components[candidate][i] + 1);
	}

	delete[] visited;
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

void tr_dfs(int v, int comp_number) {
	visited[v] = 1;
	for (const auto x : tr_list[v]) {
		if (!visited[x]) {
			tr_dfs(x, comp_number);
		}
	}
	if (comp_number >= 0)
		components[comp_number].push_back(v);
}