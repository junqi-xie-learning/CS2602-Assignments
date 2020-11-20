#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include "queue.h"

// priority_queue.h:
//
// Base Class: Queue (in "queue.h")
// Derived Class: PriorityQueue

namespace cs221
{
    template <class T>
    class PriorityQueue : public Queue<T>
    {
    protected:
        int current_length;
        T *elem;
        int max_size;
        void double_space();
        void build_heap();
        void heapify(int hole);

    public:
        PriorityQueue(int init_size = 10)
            : elem{ new T[init_size] }, max_size{ init_size }, current_length{ 0 } { }
        PriorityQueue(const T data[], int size);
        ~PriorityQueue() { delete[] elem; };

        bool is_empty() const { return current_length == 0; };
        int length() const { return current_length; }
        void enqueue(const T &x);
        T dequeue();
        T get_head() const { return elem[1]; };
    };

    template <class T>
    void PriorityQueue<T>::double_space()
    {
        T *tmp = elem;
        max_size *= 2;
        elem = new T[max_size];
        for (int i = 1; i <= current_length; ++i)
            elem[i] = tmp[i];
        delete[] tmp;
    }

    template <class T>
    void PriorityQueue<T>::heapify(int hole)
    {
        while (true)
        {
            int left = hole * 2, right = left + 1;
            
            int smallest = hole;
            if (left <= current_length && elem[left] < elem[smallest])
                smallest = left;
            if (right <= current_length && elem[right] < elem[smallest])
                smallest = right;

            if (smallest == hole)
                break;
            T tmp = elem[hole];
            elem[hole] = elem[smallest];
            elem[smallest] = tmp;
            hole = smallest;
        }
    }

    template <class T>
    void PriorityQueue<T>::build_heap()
    {
        for (int i = current_length / 2; i > 0; --i)
            heapify(i);
    }

    template <class T>
    PriorityQueue<T>::PriorityQueue(const T data[], int size)
        : max_size{ size + 10 }, current_length{ size }
    {
        elem = new T[max_size];
        for (int i = 0; i < size; i++)
            elem[i + 1] = data[i];
        build_heap();
    }

    template <class T>
    void PriorityQueue<T>::enqueue(const T &x)
    {
        if (current_length == max_size - 1)
            double_space();

        ++current_length;
        int hole = current_length;
        while (hole > 1 && x < elem[hole / 2])
        {
            elem[hole] = elem[hole / 2];
            hole /= 2;
        }
        elem[hole] = x;
    }

    template <class T>
    T PriorityQueue<T>::dequeue()
    {
        T tmp = elem[1];
        elem[1] = elem[current_length];
        --current_length;
        heapify(1);
        return tmp;
    }

} // namespace cs221

#endif