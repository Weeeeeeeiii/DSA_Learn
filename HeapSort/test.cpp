/**
 * Test program for `HeapSort.h`.
 */

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cinttypes>
#include <functional>
#include <iostream>
#include <limits>
#include <random>
#include <string_view>
#include <vector>

#include "HeapSort.h"

using Integer = std::int64_t;
using Length = std::vector<Integer>::size_type;

enum class HeapType {
  kRandom,
  kOrdered,
  kReverse,
  kRepetitive,
};

/**
 * Generate random max heap of 64-bits integral.
 */
std::vector<Integer> GenerateMaxHeap(Length length,
                                     HeapType heap_type = HeapType::kRandom) {
  std::vector<Integer> vec(length);
  std::mt19937_64 mt{std::random_device{}()};
  Integer kMax = std::numeric_limits<Integer>::max();
  Integer kMin = std::numeric_limits<Integer>::lowest();
  if (heap_type == HeapType::kRepetitive) {
    kMax = 1000000;
    kMin = -1000000;
  }
  std::uniform_int_distribution<Integer> range{kMin, kMax};
  for (Length index{0}; index < length; ++index) {
    vec[index] = range(mt);
  }

  if (heap_type == HeapType::kOrdered) {
    std::sort(vec.begin(), vec.end());
  } else if (heap_type == HeapType::kReverse) {
    std::sort(vec.begin(), vec.end(), std::greater<Integer>());
  } else
    ;

  std::make_heap(vec.begin(), vec.end());
  return vec;
}

/**
 * Check if the vector is sorted ascending order.
 */
bool IsSortedAsc(const std::vector<Integer> &vec) {
  for (Length index{1}; index < vec.size(); ++index) {
    if (vec[index - 1] > vec[index]) {
      return false;
    }
  }
  return true;
}

/**
 * Get the duration of `std::sort_heap`.
 * Reference is not used because change of vector is avoided.
 */
void CheckStdSort(std::vector<Integer> vec) {
  auto start_time{std::chrono::steady_clock::now()};
  std::sort_heap(vec.begin(), vec.end());
  auto end_time{std::chrono::steady_clock::now()};

  assert(IsSortedAsc(vec) && "Check if a max heap is passed to std::sort_heap");
  std::cout << "Test passed: std::sort_heap worked correctly!" << std::endl;

  auto duration{std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - start_time)};
  std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
}

/**
 * Get the duration of `SortHeap`.
 * Reference is not used because change of vector is avoided.
 */
void CheckMySort(std::vector<Integer> vec) {
  auto start_time{std::chrono::steady_clock::now()};
  SortHeap(vec);
  auto end_time{std::chrono::steady_clock::now()};

  assert(IsSortedAsc(vec) && "SortHeap error!");
  std::cout << "Test passed: My SortHeap worked correctly!" << std::endl;

  auto duration{std::chrono::duration_cast<std::chrono::milliseconds>(
      end_time - start_time)};
  std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
}

/**
 * Use different types and length to test the correctness and efficiency
 * of both std::sort_heap and SortHeap.
 * Print results to terminal.
 */
void Test(const Length length) {
  std::cout << "Start test with dataset number: " << length << std::endl;
  std::cout << std::endl;

  // Test random vector
  std::cout << "Random vector test:" << std::endl;
  std::vector<Integer> random_vec{GenerateMaxHeap(length, HeapType::kRandom)};
  CheckStdSort(random_vec);
  CheckMySort(random_vec);
  std::cout << std::endl;

  // Test ordered vector
  std::cout << "Ordered vector test:" << std::endl;
  std::vector<Integer> ordered_vec{GenerateMaxHeap(length, HeapType::kOrdered)};
  CheckStdSort(ordered_vec);
  CheckMySort(ordered_vec);
  std::cout << std::endl;

  // Test reverse vector
  std::cout << "Reverse vector test:" << std::endl;
  std::vector<Integer> reverse_vec{GenerateMaxHeap(length, HeapType::kReverse)};
  CheckStdSort(reverse_vec);
  CheckMySort(reverse_vec);
  std::cout << std::endl;

  // Test repetitive vector
  std::cout << "Repetitive vector test:" << std::endl;
  std::vector<Integer> repetitive_vec{
      GenerateMaxHeap(length, HeapType::kRepetitive)};
  CheckStdSort(repetitive_vec);
  CheckMySort(repetitive_vec);
  std::cout << std::endl;

  std::cout << std::endl;
}

int main() {
  // Set test dataset
  Test(1000000);
  Test(2000000);
  Test(5000000);

  return 0;
}