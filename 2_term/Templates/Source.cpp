#include <iostream>
#include <vector>
#include <algorithm>

template <class I, class O, int n = 10>
class Convert {
public:
	Convert() {
		for (int i = 0; i < n; ++i)
			arr[i] = 0;
	}
	O operator()(I &in) {
		return static_cast<O>(in);
	}
	int arr[n];
};

//template <>
//class Convert<double, int> {
//public:
//	int operator()(double &in) {
//		return static_cast<int>(in + 0.5);
//	}
//};

using namespace std;

int main() {
	Convert<double, int, 20> conv;
	vector<double> dv = { 1.1, 1.6, 2.3 };
	vector<int> iv;
	iv.resize(dv.size());
	transform(dv.begin(), dv.end(), iv.begin(), conv);
	for (auto x : iv)
		cout << x << ' ';
	cout << endl;
	return 0;
}