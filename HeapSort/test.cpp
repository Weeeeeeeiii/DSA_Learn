/**
 * test program for HeapSort.h.
 */

#include "HeapSort.h"
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> array{1, 2, 3, 4, 5, 6, 7};
    std::vector<int> array2{array};
    std::make_heap(array.begin(), array.end());
    std::make_heap(array2.begin(), array2.end());
    std::cout << "heap element: ";
    for (auto &i : array)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    SortHeap(array);
    std::cout << "SortHeap element: ";
    for (auto &i : array)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::sort_heap(array2.begin(), array2.end());
    std::cout << "heap sorted element: ";
    for (auto &i : array2)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}