#ifndef SORTING
#define SORTING

#include <iostream>

namespace cs221
{
    template <class T>
    void insertion_sort(T list[], int length)
    {
        for (int i = 1; i < length; ++i)
        {
            T tmp = list[i];
            int j = i - 1;
            while (j >= 0 && tmp < list[j])
            {
                list[j + 1] = list[j];
                --j;
            }
            list[j + 1] = tmp;
        }
    }


    template <class T>
    void shell_sort(T list[], int length)
    {
        for (int step = length / 2; step > 0; step /= 2)
        {
            for (int i = step; i < length; ++i)
            {
                T tmp = list[i];
                int j = i - step;
                while (j >= 0 && list[j] > tmp)
                {
                    list[j + step] = list[j];
                    j -= step;
                }
                list[j + step] = tmp;
            }
        }
    }


    template <class T>
    void selection_sort(T list[], int length)
    {
        for (int i = 0; i < length - 1; ++i)
        {
            int min = i;
            for (int j = i + 1; j < length; ++j)
            {
                if (list[j] < list[min])
                    min = j;
                int tmp = list[i];
                list[i] = list[min];
                list[min] = tmp;
            }
        }
    }


    template <class T>
    void max_heapify(T list[], int hole, int length)
    {
        while (true)
        {
            int left = hole * 2 + 1, right = left + 1;

            int largest = hole;
            if (left < length && list[left] > list[largest])
                largest = left;
            if (right < length && list[right] > list[largest])
                largest = right;

            if (largest == hole)
                break;
            T tmp = list[hole];
            list[hole] = list[largest];
            list[largest] = tmp;
            hole = largest;
        }
    }

    template <class T>
    void heap_sort(T list[], int length)
    {
        for (int i = length / 2 - 1; i >= 0; --i)
            max_heapify(list, i, length);
        for (int i = length - 1; i > 0; --i)
        {
            int tmp = list[0];
            list[0] = list[i];
            list[i] = tmp;
            max_heapify(list, 0, i);
        }
    }


    template <class T>
    void bubble_sort(T list[], int length)
    {
        bool flag = true;
        for (int i = 1; i < length && flag; ++i)
        {
            flag = false;
            for (int j = 0; j < length - i; ++j)
            {
                if (list[j + 1] < list[j])
                {
                    int tmp = list[j];
                    list[j] = list[j + 1];
                    list[j + 1] = tmp;
                    flag = true;
                }
            }
        }
    }


    template <class T>
    int divide(T list[], int low, int high)
    {
        T key = list[low];
        do
        {
            while (low < high && list[high] >= key)
                --high;
            if (low < high)
            {
                list[low] = list[high];
                ++low;
            }

            while (low < high && list[low] <= key)
                ++low;
            if (low < high)
            {
                list[high] = list[low];
                --high;
            }
        } while (low != high);
        list[low] = key;
        return low;
    }

    template <class T>
    void quick_sort(T list[], int low, int high)
    {
        if (low >= high)
            return;
        int mid = divide(list, low, high);
        quick_sort(list, low, mid - 1);
        quick_sort(list, mid + 1, high);
    }

    template <class T>
    void quick_sort(T list[], int length)
    {
        quick_sort(list, 0, length - 1);
    }


    template <class T>
    void merge(T list[], int left, int mid, int right)
    {
        T *tmp = new T[right - left + 1];
        int i = left, j = mid, k = 0;
        while (i < mid && j <= right)
        {
            if (list[i] < list[j])
            {
                tmp[k] = list[i];
                ++i;
            }
            else
            {
                tmp[k] = list[j];
                ++j;
            }
            ++k;
        }
        while (i < mid)
        {
            tmp[k] = list[i];
            ++i, ++k;
        }
        while (j <= right)
        {
            tmp[k] = list[j];
            ++j, ++k;
        }

        i = left, k = 0;
        while (i <= right)
        {
            list[i] = tmp[k];
            ++i, ++k;
        }
        delete[] tmp;
    }

    template <class T>
    void merge_sort(T list[], int left, int right)
    {
        int mid = (left + right) / 2;
        if (left == right)
            return;
        merge_sort(list, left, mid);
        merge_sort(list, mid + 1, right);
        merge(list, left, mid + 1, right);
    }

    template <class T>
    void merge_sort(T list[], int length)
    {
        merge_sort(list, 0, length - 1);
    }

} // namespace cs221

#endif