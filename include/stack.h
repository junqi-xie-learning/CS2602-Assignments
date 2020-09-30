#include <iostream>

// stack.h:
//
// Base Class: Stack
// Derived Class: SeqStack, LinkStack

namespace cs221
{
    template <class T>
    class Stack
    {
    public:
        virtual bool is_empty() const = 0;
        virtual void push(const T &x) = 0;
        virtual T pop() = 0;
        virtual T top() const = 0;
        virtual ~Stack() { }
    };


    template <class T>
    class SeqStack : public Stack<T>
    {
    private:
        T *elem;
        int top_p;
        int max_size;
        void double_space();

    public:
        SeqStack(int init_size = 10)
            : elem{ new T[init_size] }, max_size{ init_size }, top_p{ -1 } { }
        ~SeqStack() { delete[] elem; }

        bool is_empty() const { return top_p == -1; }
        void push(const T &x);
        T pop();
        T top() const { return elem[top_p]; }
    };

    template <class T>
    void SeqStack<T>::double_space()
    {
        T *tmp = elem;
        elem = new T[2 * max_size];
        for (int i = 0; i < max_size; ++i)
            elem[i] = tmp[i];
        max_size *= 2;
        delete[] tmp;
    }

    template <class T>
    void SeqStack<T>::push(const T &x)
    {
        if (top_p == max_size - 1)
            double_space();
        ++top_p;
        elem[top_p] = x;
    }

    template <class T>
    T SeqStack<T>::pop()
    {
        T x = elem[top_p];
        --top_p;
        return x;
    }


    template <class T>
    class LinkStack : public Stack<T>
    {
    private:
        struct Node
        {
            T data;
            Node *next;
            Node(const T &x, Node *N = nullptr)
                : data{ x }, next{ N } { }
            Node() : next{ nullptr } { }
            ~Node() { }
        };

        Node *top_p;

    public:
        LinkStack()
            : top_p{ nullptr } { }
        ~LinkStack();

        bool is_empty() const { return top_p == nullptr; }
        void push(const T &x);
        T pop();
        T top() const { return top_p->data; }
    };

    template <class T>
    LinkStack<T>::~LinkStack()
    {
        while (top_p)
        {
            Node *tmp = top_p;
            top_p = top_p->next;
            delete tmp;
        }
    }

    template <class T>
    void LinkStack<T>::push(const T &x)
    {
        top_p = new Node{ x, top_p };
    }

    template <class T>
    T LinkStack<T>::pop()
    {
        Node *tmp = top_p;
        T x = tmp->data;
        top_p = top_p->next;
        delete tmp;
        return x;
    }

} // namespace cs221