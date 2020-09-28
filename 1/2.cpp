#include <iostream>
using namespace std;

template <class elemType>
class linkList
{
private:
    struct node
    {
        elemType data;
        node *prev;
        node *next;
        node(const elemType &x, node *p = nullptr, node *n = nullptr)
            : data{ x }, prev{ p }, next{ n } { }
        ~node() { }
    };
    node *head;

public:
    linkList()
        : head{ new node{ 0 } } { head->prev = head; head->next = head; }
    ~linkList() { clear(); delete head; }

    void insert(int i, const elemType &x);
    void remove(int i);

    void clear();
    void traverse() const;
};

template <class elemType>
void linkList<elemType>::insert(int i, const elemType &x)
{
    if (i <= head->data / 2)
    {
        node *p = head;
        for (; i > 0; --i)
            p = p->next;

        node *tmp = new node{ x, p, p->next };
        p->next = tmp;
        tmp->next->prev = tmp;
    }
    else
    {
        node *p = head;
        for (i = head->data - i; i > 0; --i)
            p = p->prev;

        node *tmp = new node{ x, p->prev, p };
        p->prev = tmp;
        tmp->prev->next = tmp;
    }
    ++head->data;
}

template <class elemType>
void linkList<elemType>::remove(int i)
{
    if (i <= head->data / 2)
    {
        node *p = head;
        for (; i > 0; --i)
            p = p->next;

        node *tmp = p->next;
        p->next = tmp->next;
        p->next->prev = p;
        delete tmp;
    }
    else
    {
        node *p = head;
        for (i = head->data - i; i > 0; --i)
            p = p->prev;

        node *tmp = p->prev;
        p->prev = tmp->prev;
        p->prev->next = p;
        delete tmp;
    }
    --head->data;
}

template <class elemType>
void linkList<elemType>::clear()
{
    for (node *p = head->next; p != head; )
    {
        node *q = p->next;
        delete p;
        p = q;
    }
    head->next = head;
    head->prev = head;
    head->data = 0;
}

template <class elemType>
void linkList<elemType>::traverse() const
{
    for (node *p = head->next; p != head; p = p->next)
        cout << p->data << ' ';
}

int main()
{
    int n = 0, m = 0;
    cin >> n >> m;

    linkList<int> list;
    for (int i = 0; i < n; ++i)
    {
        int number = 0;
        cin >> number;
        list.insert(i, number);
    }

    for (int i = 0; i < m; ++i)
    {
        int token = 0;
        cin >> token;

        int x = 0, y = 0;
        switch (token)
        {
        case 1:
            cin >> x >> y;
            list.insert(x, y);
            break;
        case 2:
            cin >> x;
            list.remove(x - 1);
            break;
        }
    }

    list.traverse();
    return 0;
}