#ifndef LIST
#define LIST

#include <iostream>

// list.h:
// 
// Base Class: List
// Derived Class: SeqList, LinkList

namespace cs221
{
    template <class T>
    class List
    {
    public:
        virtual void clear() = 0;
        virtual int length() const = 0;
        virtual void insert(int i, const T &x) = 0;
        virtual void append(const T &x) = 0;
        virtual T remove(int i) = 0;
        virtual int find(const T &x) const = 0;
        virtual const T &visit(int i) const = 0;
        virtual T &visit(int i) = 0;
        virtual void traverse() const = 0;
        virtual ~List() { };
    };
    

    template <class T>
    class SeqList : public List<T>
    {
    protected:
        T *elem;
        int current_length;
        int max_size;
        void double_space();

    public:
        SeqList(int init_size = 10)
            : elem{ new T[init_size] }, max_size{ init_size }, current_length{ 0 } { };
        SeqList(const SeqList &other);
        ~SeqList() { delete[] elem; }
        void clear() { current_length = 0; }

        int length() const { return current_length; }
        void insert(int i, const T &x);
        void append(const T &x) { insert(length(), x); }
        T remove(int i);
        int find(const T &x) const;

        const T &visit(int i) const { return elem[i]; }
        T &visit(int i) { return elem[i]; }
        void traverse() const;
    };

    template <class T>
    SeqList<T>::SeqList(const SeqList &other)
        : elem{ new T[other.max_size] }, max_size{ other.max_size }, current_length{ other.current_length }
    {
        for (int i = 0; i < current_length; ++i)
            elem[i] = other.elem[i];
    }

    template <class T>
    void SeqList<T>::double_space()
    {
        T *tmp = elem;
        max_size *= 2;
        elem = new T[max_size];
        for (int i = 0; i < current_length; ++i)
            elem[i] = tmp[i];
        delete[] tmp;
    }

    template <class T>
    void SeqList<T>::insert(int i, const T &x)
    {
        if (current_length == max_size)
            double_space();
        for (int j = current_length; j > i; --j)
            elem[j] = elem[j - 1];
        elem[i] = x;
        ++current_length;
    }

    template <class T>
    T SeqList<T>::remove(int i)
    {
        T x = elem[i];
        for (int j = i; j < current_length - 1; ++j)
            elem[j] = elem[j + 1];
        --current_length;
        return x;
    }

    template <class T>
    int SeqList<T>::find(const T &x) const
    {
        for (int i = 0; i < current_length; ++i)
            if (elem[i] == x)
                return i;
        return -1;
    }

    template <class T>
    void SeqList<T>::traverse() const
    {
        for (int i = 0; i < current_length; ++i)
            std::cout << elem[i] << ' ';
    }


    template <class T>
    class LinkList : public List<T>
    {
    protected:
        struct Node
        {
            T data;
            Node *next;
            Node(const T &x, Node *n = nullptr)
                : data{ x }, next{ n } { }
            Node() : next{ nullptr } { }
            ~Node() { }
        };

        Node *head;
        Node *tail;
        int current_length;
        Node *move(int i) const;

    public:
        LinkList()
            : head{ new Node{ } }, current_length{ 0 } { }
        LinkList(const LinkList &other);
        ~LinkList() { clear(); delete head; }
        void clear();

        int length() const { return current_length; }
        void insert(int i, const T &x);
        void append(const T &x);
        T remove(int i);
        int find(const T &x) const;

        const T &visit(int i) const { return move(i)->data; }
        T &visit(int i) { return move(i)->data; }
        void traverse() const;
    };

    template <class T>
    LinkList<T>::LinkList(const LinkList &other)
        : head{ new Node{ } }, current_length{ 0 }
    {
        Node *p = head;
        for (Node *q = other.head->next; q; q = q->next)
        {
            p->next = new Node{ q->data };
            p = p->next;
            ++current_length;
        }
    }

    template <class T>
    typename LinkList<T>::Node *LinkList<T>::move(int i) const
    {
        Node *p = head;
        for (; i >= 0; --i)
            p = p->next;
        return p;
    }

    template <class T>
    void LinkList<T>::clear()
    {
        Node *p = head->next;
        head->next = nullptr;
        while (p)
        {
            Node *q = p->next;
            delete p;
            p = q;
        }
        current_length = 0;
    }

    template <class T>
    void LinkList<T>::insert(int i, const T &x)
    {
        Node *pos = move(i - 1);
        pos->next = new Node{ x, pos->next };
        ++current_length;
        if (pos == tail)
            tail = tail->next;
    }

    template <class T>
    void LinkList<T>::append(const T &x)
    {
        tail->next = new Node{ x };
        tail = tail->next;
    }

    template <class T>
    T LinkList<T>::remove(int i)
    {
        Node *pos = move(i - 1);
        Node *delp = pos->next;

        T x = delp->data;
        pos->next = delp->next;
        delete delp;
        --current_length;
        if (!pos->next)
            tail = pos;
        return x;
    }

    template <class T>
    int LinkList<T>::find(const T &x) const
    {
        int i = 0;
        for (Node *p = head->next; p; p = p->next)
        {
            if (p->data == x)
                return i;
            ++i;
        }
        return -1;
    }

    template <class T>
    void LinkList<T>::traverse() const
    {
        for (Node *p = head->next; p; p = p->next)
            std::cout << p->data << ' ';
    }

} // namespace cs221

#endif