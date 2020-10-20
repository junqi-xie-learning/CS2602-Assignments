#include <iostream>

// queue.h:
//
// Base Class: Queue
// Derived Class: SeqQueue, LinkQueue

namespace cs221
{
    template <class T>
    class Queue
    {
    public:
        virtual bool is_empty() const = 0;
        virtual void enqueue(const T &x) = 0;
        virtual T dequeue() = 0;
        virtual T get_head() const = 0;
        virtual ~Queue() { }
    };


    template <class T>
    class SeqQueue : public Queue<T>
    {
    protected:
        T *elem;
        int max_size;
        int front, rear;
        void double_space();
        int move(int i) const { return i % max_size; }

    public:
        SeqQueue(int init_size = 10)
            : elem{ new T[init_size] }, max_size{ init_size }, front{ 0 }, rear{ 0 } { }
        SeqQueue(const SeqQueue &other);
        ~SeqQueue() { delete[] elem; }

        bool is_empty() const { return front == rear; }
        void enqueue(const T &x);
        T dequeue();
        T get_head() const { return elem[move(front + 1)]; }
    };

    template <class T>
    void SeqQueue<T>::double_space()
    {
        T *tmp = elem;
        elem = new T[2 * max_size];
        for (int i = 1; i < max_size; ++i)
            elem[i] = tmp[move(front + i)];
        front = 0;
        rear = max_size - 1;
        max_size *= 2;
        delete tmp;
    }

    template <class T>
    SeqQueue<T>::SeqQueue(const SeqQueue &other)
        : elem{ new T[other.max_size] }, max_size{ other.max_size }, front{ other.front }, rear{ other.rear }
    {
        for (int i = 0; i < max_size; ++i)
            elem[i] = other.elem[i];
    }

    template <class T>
    void SeqQueue<T>::enqueue(const T &x)
    {
        if (move(rear + 1) == front)
            double_space();
        rear = move(rear + 1);
        elem[rear] = x;
    }

    template <class T>
    T SeqQueue<T>::dequeue()
    {
        front = move(front + 1);
        return elem[front];
    }


    template <class T>
    class LinkQueue : public Queue<T>
    {
    protected:
        struct Node
        {
            T data;
            Node *next;
            Node(const T &x, Node *N = nullptr)
                : data{ x }, next{ N } { }
            Node() : next{ nullptr } { }
            ~Node() { }
        };

        Node *front, *rear;

    public:
        LinkQueue()
            : front{ nullptr }, rear{ nullptr } { }
        LinkQueue(const LinkQueue &other);
        ~LinkQueue();

        bool is_empty() const { return front == nullptr; }
        void enqueue(const T &x);
        T dequeue();
        T get_head() const { return front->data; }
    };

    template <class T>
    LinkQueue<T>::LinkQueue(const LinkQueue &other)
        : front{ new Node{ other.front->data } }, rear{ nullptr }
    {
        Node *p = front;
        for (Node *q = other.front->next; q; q = q->next)
        {
            p->next = new Node{ q->data };
            p = p->next;
            if (!q->next)
                rear = p;
        }
    }

    template <class T>
    LinkQueue<T>::~LinkQueue()
    {
        while (front)
        {
            Node *tmp = front;
            front = front->next;
            delete tmp;
        }
    }

    template <class T>
    void LinkQueue<T>::enqueue(const T &x)
    {
        Node *tmp = new Node{ x };
        if (!rear)
        {
            rear = tmp;
            front = rear;
        }
        else
        {
            rear->next = tmp;
            rear = rear->next;
        }
    }

    template <class T>
    T LinkQueue<T>::dequeue()
    {
        Node *tmp = front;
        T value = front->data;
        front = front->next;
        if (!front)
            rear = nullptr;
        delete tmp;
        return value;
    }

} // namespace cs221