#ifndef HASH_TABLE
#define HASH_TABLE

#include <iostream>

// hash_table.h:
//
// Class: HashTable

namespace cs221
{
    template <class T>
    class HashTable
    {
    protected:
        struct Node
        {
            T data;
            Node *next;
            Node(const T &d, Node *n = nullptr)
                : data{ d }, next{ n } { }
            Node()
                : next{ nullptr } { }
        };

        Node **elem;
        int size;
        int (*key)(const T &x);
        static int defaultKey(const T &x) { return std::abs(x); }

    public:
        HashTable(int length = 101, int (*f)(const T &x) = defaultKey)
            : size{ length }, elem{ new Node*[length]{ } }, key{ f } { }
        ~HashTable();

        T *find(const T &x) const;
        void insert(const T &x);
        void remove(const T &x);
    };

    template <class T>
    HashTable<T>::~HashTable()
    {
        for (int i = 0; i < size; ++i)
        {
            Node *p = elem[i];
            while (p)
            {
                Node *q = p->next;
                delete p;
                p = q;
            }
        }
        delete[] elem;
    }

    template <class T>
    T *HashTable<T>::find(const T &x) const
    {
        const int pos = key(x) % size;
        for (Node *p = elem[pos]; p; p = p->next)
            if (p->data == x)
                return &(p->data);
        return nullptr;
    }

    template <class T>
    void HashTable<T>::insert(const T &x)
    {
        int pos = key(x) % size;
        elem[pos] = new Node{ x, elem[pos] };
    }

    template <class T>
    void HashTable<T>::remove(const T &x)
    {
        int pos = key(x) % size;
        if (!elem[pos])
            return;

        Node *p = elem[pos];
        if (elem[pos]->data == x)
        {
            elem[pos] = p->next;
            delete p;
        }
        else
            while (p->next)
                if (p->next->data == x)
                {
                    Node *q = p->next;
                    p->next = q->next;
                    delete q;
                    return;
                }
    }

} // namespace cs221

#endif