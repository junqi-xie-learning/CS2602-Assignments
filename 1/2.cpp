#include <iostream>
using namespace std;

template <class elemType>
class linkList
{
private:
    struct node
    {
        elemType data;
        node *next;
        node(const elemType &x, node *p = nullptr)
            : data{ x }, next{ p } { }
        node()
            : next{ nullptr } { }
        ~node() { }
    };
    node *head;
    node *tail;

public:
    linkList()
        : head{ new node{ } }, tail{ head } { }
    ~linkList() { clear(); delete head; }

    void insert(int i, const elemType &x);
    void append(const elemType &x);
    void remove(int i);

    void clear();
    void traverse() const;
};

template <class elemType>
void linkList<elemType>::insert(int i, const elemType &x)
{
    node *p = head;
    for (; i > 0; --i)
        p = p->next;

    node *tmp = new node{ x, p->next };
    p->next = tmp;
    if (!tmp->next)
        tail = tmp;
}

template <class elemType>
void linkList<elemType>::append(const elemType &x)
{
    node *tmp = new node{ x };
    tail->next = tmp;
    tail = tmp;
}

template <class elemType>
void linkList<elemType>::remove(int i)
{
    node *p = head;
    for (; i > 0; --i)
        p = p->next;

    node *tmp = p->next;
    p->next = tmp->next;
    delete tmp;
    if (!p->next)
        tail = p;
}

template <class elemType>
void linkList<elemType>::clear()
{
    for (node *p = head->next; p; )
    {
        node *q = p->next;
        delete p;
        p = q;
    }
    head->next = nullptr;
    tail = head;
}

template <class elemType>
void linkList<elemType>::traverse() const
{
    for (node *p = head->next; p; p = p->next)
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
        list.append(number);
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