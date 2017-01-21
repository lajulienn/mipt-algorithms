/**
 * @author Julia Ivanova
 */

#include <iostream>
#include <vector>

#include "rmq.h"

int main() {
  int array_size;
  int test_count;
  std::cin >> array_size >> test_count;

  std::vector<int> array(array_size);
  for (int i = 0; i < array_size; ++i) {
    std::cin >> array[i];
  }

  Rmq rmq(array);

  for(int i = 0; i < test_count; ++i) {
    int from, to;
    std::cin >> from >> to;
    std::cout << rmq.GetSecondElement(from - 1, to - 1) << std::endl;
  }

  return 0;
}