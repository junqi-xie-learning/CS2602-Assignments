#include "../../include/list.h"
#include <cstring>
using namespace cs221;
using namespace std;


template <class T>
class ExtendedLinkList : public LinkList<T>
{
public:
    ExtendedLinkList()
        : LinkList<T>{ } { }

    void read(int n);
    ExtendedLinkList &operator+=(ExtendedLinkList &other);
};

template <typename T>
void ExtendedLinkList<T>::read(int n)
{
    typename LinkList<T>::Node *p = this->head;
    for (int i = 0; i < n; ++i)
    {
        T t;
        cin >> t;
        p->next = new typename LinkList<T>::Node{ t };
        p = p->next;
    }
}

template <class T>
ExtendedLinkList<T> &ExtendedLinkList<T>::operator+=(ExtendedLinkList<T> &other)
{
    typename LinkList<T>::Node *p = this->head;
    while (p->next)
        p = p->next;
    
    typename LinkList<T>::Node *q = other.head->next;
    while (q)
    {
        p->next = new typename LinkList<T>::Node{ q->data };
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
        ExtendedLinkList<int> l, l2;
        l.read(n);
        l2.read(m);
        l += l2;
        l.traverse();
    }
    else if (strcmp(type, "char") == 0)
    {
        ExtendedLinkList<char> l, l2;
        l.read(n);
        l2.read(m);
        l += l2;
        l.traverse();
    }
    else if (strcmp(type, "double") == 0)
    {
        ExtendedLinkList<double> l, l2;
        l.read(n);
        l2.read(m);
        l += l2;
        l.traverse();
    }
    return 0;
}