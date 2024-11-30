/**
 * Provide personal implementation of heap sort.
 */

#ifndef HEAP_SORT_H_
#define HEAP_SORT_H_

#include <utility>
#include <vector>

/**
 * Recursively swap the maximum with the parent node.
 * Namely heapify a subtree rooted with node `index`.
 * `length` represents `length of vector - length of elements has been sorted`.
 */
template <typename T>
void Heapify(std::vector<T> &vec, typename std::vector<T>::size_type length,
             typename std::vector<T>::size_type index = 0) {
  auto left_child{index * 2 + 1};
  auto right_child{left_child + 1};
  auto largest{index};

  if (left_child < length && vec[left_child] > vec[largest]) {
    largest = left_child;
  }
  if (right_child < length && vec[right_child] > vec[largest]) {
    largest = right_child;
  }

  if (largest != index) {
    std::swap(vec[index], vec[largest]);
    Heapify(vec, length, largest);
  }
}

/**
 * Only sort max heap. Do not convert vector to heap or check if input is a max
 * heap.
 */
template <typename T>
void SortHeap(std::vector<T> &vec) {
  auto length{vec.size()};
  if (length < 2) {
    return;
  }
  for (auto index{length - 1}; index > 0; --index) {
    std::swap(vec[0], vec[index]);
    Heapify(vec, index);
  }
}

#endif