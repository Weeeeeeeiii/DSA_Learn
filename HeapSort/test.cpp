/**
 * test program for HeapSort.h.
 */

#include <algorithm>
#include <iostream>
#include <vector>

#include "HeapSort.h"

int main() {
  std::vector<int> vec{1, 2, 3, 4, 5, 6, 7};
  std::vector<int> vec2{1, 2, 3, 4, 5, 6, 7};
  std::make_heap(vec.begin(), vec.end());
  std::make_heap(vec2.begin(), vec2.end());
  std::cout << "heap element: ";
  for (auto &i : vec) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  SortHeap(vec);
  std::cout << "SortHeap element: ";
  for (auto &i : vec) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  std::sort_heap(vec2.begin(), vec2.end());
  std::cout << "heap sorted element: ";
  for (auto &i : vec2) {
    std::cout << i << " ";
  }
  std::cout << std::endl;

  return 0;
}