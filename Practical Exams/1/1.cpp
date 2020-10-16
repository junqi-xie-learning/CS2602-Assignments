#include <iostream>
#include <cstring>
using namespace std;


template <class T>
class LinkList //: public List<T>
{
public:
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
    void append(const T &x) { insert(length(), x); }
    T remove(int i);
    int search(const T &x) const;

    const T &visit(int i) const { return move(i)->data; }
    T &visit(int i) { return move(i)->data; }
    void traverse() const;

    void read(int n);
    LinkList &operator+=(LinkList &other);
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
    return x;
}

template <class T>
int LinkList<T>::search(const T &x) const
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

template <typename T>
void LinkList<T>::read(int n)
{
    Node *p = head;
    for (int i = 0; i < n; ++i)
    {
        T t;
        cin >> t;
        p->next = new Node{ t };
        p = p->next;
    }
}

template <class T>
LinkList<T> &LinkList<T>::operator+=(LinkList<T> &other)
{
    Node *p = head;
    while (p->next)
        p = p->next;
    
    Node *q = other.head->next;
    while (q)
    {
        p->next = new Node{ q->data };
        p = p->next;
        q = q->next;
    }
    return *this;
}


int main()
{
    char type[10];
    cin >> type;
    int n, m;
    cin >> n >> m;

    if (strcmp(type, "int") == 0)
    {
        LinkList<int> l, l2;
        l.read(n);
        l2.read(m);
        l += l2;
        l.traverse();
    }
    else if (strcmp(type, "char") == 0)
    {
        LinkList<char> l, l2;
        l.read(n);
        l2.read(m);
        l += l2;
        l.traverse();
    }
    else if (strcmp(type, "double") == 0)
    {
        LinkList<double> l, l2;
        l.read(n);
        l2.read(m);
        l += l2;
        l.traverse();
    }
    return 0;
}