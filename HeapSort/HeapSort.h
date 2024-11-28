/**
 * Provide personal implementation of heap sort.
 */
#ifndef HEAP_SORT_H_
#define HEAP_SORT_H_

#include <vector>
#include <utility>

/**
 * Recursively swap the maximum with the parent node.
 * Namely heapify a subtree rooted with node `index`.
 * `length` represents `length of vector - length of elements has been sorted`.
 */
template <typename T>
void Heapify(std::vector<T> &array, std::size_t length, std::size_t index)
{
    auto left_child{index * 2 + 1};
    auto right_child{left_child + 1};
    auto largest{index};

    if (left_child < length && array[left_child] > array[largest])
    {
        largest = left_child;
    }
    if (right_child < length && array[right_child] > array[largest])
    {
        largest = right_child;
    }

    if (largest != index)
    {
        std::swap(array[index], array[largest]);
        Heapify(array, length, largest);
    }
}

/**
 * Only sort max heap. Do not convert vector to heap or check if input is a max
 * heap.
 */
template <typename T>
void SortHeap(std::vector<T> &array)
{
    for (auto length{std::ssize(array) - 1}; length > 0; --length)
    {
        std::swap(array.data()[0], array.data()[length]);
        Heapify(array, static_cast<std::size_t> (length), 0);
    }
}
#endif