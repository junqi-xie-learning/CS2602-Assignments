#include "../include/stack.h"
using namespace std;
using namespace cs221;

struct Person
{
    int number;
    int urgency;
};

class TicketQueue : SeqStack<Person>
{
public:
    TicketQueue(int init_size)
        : SeqStack<Person>{ init_size } { }
    void enqueue(const Person &x, int attempts);
    void output();
};

void TicketQueue::enqueue(const Person &x, int attempts)
{
    push(x);
    int index = top_p;
    while (index > 0 && elem[index - 1].urgency < x.urgency && attempts > 0)
    {
        swap(elem[index - 1], elem[index]);
        --index;
        --attempts;
    }
}

void TicketQueue::output()
{
    for (int i = 0; i <= top_p; ++i)
        cout << elem[i].number << ' ';
}


int main()
{
    int n = 0;
    cin >> n;

    TicketQueue tq{ n };
    for (int i = 1; i <= n; ++i)
    {
        int a = 0, c = 0;
        cin >> a >> c;
        tq.enqueue(Person{ i, a }, c);
    }
    tq.output();
    return 0;
}