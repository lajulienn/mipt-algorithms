#include <iostream>
#include <ctime>
#include <vector>
#include "rb_tree.h"

using namespace std;

int main() {
	while (true) {
		RB_tree<int> tree;
		int N;
		cout << "Enter a number of elements:" << endl;
		cin >> N;
		clock_t start, stop;
		srand(time(NULL));
		std::vector<int> data(N);
		for (int i = 0; i < N; ++i)
			data[i] = rand();
		std::vector<int> data2(N);
		for (int i = 0; i < N; ++i)
			data2[i] = rand();

		start = clock();
		for (int i = 0; i < N; ++i)
			tree.RbInsert(data[i]);
		stop = clock();
		cout << "Insert time = " << (double)(stop - start) / CLOCKS_PER_SEC << endl;

		//cout << "***\n";
		//tree.Dump();
		//cout << "***\n";

		start = clock();
		for (int i = 0; i < N; ++i)
			std::cout << tree.TreeSearch(data[i])->key << ' ';
		stop = clock();
		cout << "Search time = " << (double)(stop - start) / CLOCKS_PER_SEC << endl;

		start = clock();
		for (int i = 0; i < N; ++i)
			tree.RbDelete(data[i]);		
		stop = clock();
		cout << "Delete time = " << (double)(stop - start) / CLOCKS_PER_SEC << endl;


		//cout << "***\n";
		//tree.Dump();
		//cout << "***\n";
	}
	return 0;
}