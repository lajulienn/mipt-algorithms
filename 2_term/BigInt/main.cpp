#include <iostream>
#include "bigint.h"

using namespace std;

int main() {
	BigInt n1, n2;
	n1.scan();
	n2.scan();

	n1 = n1 * n2;

	n1.print();

	return 0;
}