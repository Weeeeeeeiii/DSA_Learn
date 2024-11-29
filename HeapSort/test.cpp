/**
 * Test program for `HeapSort.h`.
 */

#include "HeapSort.h"
#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cinttypes>
#include <string_view>

using Length = std::vector<int64_t>::size_type;

enum class HeapType {
  kRandom,
  kAscending,
  kDescending,
  kRepeat,
};

/**
 * Generate random max heap of 64-bits integral.
 */
std::vector<int64_t> GenerateMaxHeap(Length length, 
                                     HeapType heap_type = HeapType::kRandom) {
  std::mt19937_64 mt{std::random_device{}()};
  std::vector<int64_t> vec(length);

  if (heap_type == HeapType::kRepeat) {
    const int64_t kMax = 1000000;
    const int64_t kMin = -1000000;
    std::uniform_int_distribution<int64_t> range{kMin, kMax};
    for (Length index{0}; index < length; ++index) {
      vec[index] = range(mt);
    }
  } else {
    for (Length index{0}; index < length; ++index) {
      vec[index] = mt();
    }
  }

  if (heap_type == HeapType::kAscending) {
    std::sort(vec.begin(), vec.end());
  } else if (heap_type == HeapType::kDescending) {
    std::sort(vec.begin(), vec.end(), std::greater<int64_t>());
  } else 
    ;

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
  // Random vector test
  std::vector<int64_t> random_vec{GenerateMaxHeap(10000000)};
  std::cout << (IsSortedAsc(random_vec) ? "Is" : "Not") << " sorted. " 
  << std::endl;

  SortHeap(random_vec);
  std::cout << (IsSortedAsc(random_vec) ? "Is" : "Not") << " sorted. " 
  << std::endl;

  // Ascent vector test
  std::vector<int64_t> ascent_vec{
      GenerateMaxHeap(10000000, HeapType::kAscending)};
  std::cout << (IsSortedAsc(ascent_vec) ? "Is" : "Not") << " sorted. " 
  << std::endl;

  SortHeap(ascent_vec);
  std::cout << (IsSortedAsc(ascent_vec) ? "Is" : "Not") << " sorted. " 
  << std::endl;  
  
  // Descent vector test
  std::vector<int64_t> descent_vec{
      GenerateMaxHeap(10000000, HeapType::kDescending)};
  std::cout << (IsSortedAsc(descent_vec) ? "Is" : "Not") << " sorted. " 
  << std::endl;

  SortHeap(descent_vec);
  std::cout << (IsSortedAsc(descent_vec) ? "Is" : "Not") << " sorted. " 
  << std::endl;  
  
  // Repeated vector test
  std::vector<int64_t> repeated_vec{
      GenerateMaxHeap(10000000, HeapType::kRepeat)};
  std::cout << (IsSortedAsc(repeated_vec) ? "Is" : "Not") << " sorted. " 
  << std::endl;

  SortHeap(repeated_vec);
  std::cout << (IsSortedAsc(repeated_vec) ? "Is" : "Not") << " sorted. " 
  << std::endl;

  return 0;
}