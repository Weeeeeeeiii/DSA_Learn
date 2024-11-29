/**
 * Test program for `HeapSort.h`.
 */

#include "HeapSort.h"
#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cinttypes>

using Length = std::vector<int64_t>::size_type;

/**
 * Generate random max heap of 64-bits integral.
 */
std::vector<int64_t> GenerateMaxHeap(Length length) {
  std::mt19937_64 mt{std::random_device{}()};
  std::vector<int64_t> vec(length);
  for (Length index{0}; index < length; ++index) {
    vec[index] = mt();
  }
  std::make_heap(vec.begin(), vec.end());
  return vec;
}

/**
 * Check if the vector is sorted ascending order.
 */
bool IsSortedAsc(const std::vector<int64_t> &vec) {
  for (Length index{1}; index < vec.size(); ++index) {
    if (vec[index - 1] > vec[index]) {
      return false;
    }
  }
  return true;
}

int main() {
  std::vector<int64_t> vec{GenerateMaxHeap(10)};
  std::vector<int64_t> vec2{vec};

  std::cout << "Ordinary max heap:" << std::endl;
  for (auto element : vec) {
    std::cout << element << " ";
  }
  std::cout << std::endl << std::endl;

  SortHeap(vec);
  std::cout << "Sorted max heap by SortHeap:" << std::endl;
  for (auto element : vec) {
    std::cout << element << " ";
  }
  std::cout << std::endl;
  std::cout << "Sorted correctly? " << IsSortedAsc(vec) 
  << std::endl << std::endl;

  std::sort_heap(vec2.begin(), vec2.end());
  std::cout << "Sorted max heap by std::sort_heap:" << std::endl;
  for (auto element : vec) {
    std::cout << element << " ";
  }
  std::cout << std::endl << std::endl;
}