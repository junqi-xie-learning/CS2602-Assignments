#ifndef SEARCHING
#define SEARCHING

#include <iostream>

// sorting.h:
//
// Algorithm: linear_search, binary_search

namespace cs221
{
    template <class T>
    int linear_search(const T list[], int length, const T &x)
    {
        for (int i = 0; i < length; ++i)
            if (list[i] == x)
                return i;
        return -1;
    }

    template <class T>
    int binary_search(const T list[], int length, const T &x)
    {
        int low = 0, high = length - 1;
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (list[mid] == x)
                return mid;
            else if (list[mid] < x)
                high = mid - 1;
            else
                low = mid + 1;
        }
        return -1;
    }

} // namespace cs221

#endif