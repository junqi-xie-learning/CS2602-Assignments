#include "../../include/list.h"
using namespace std;
using namespace cs221;

struct Person
{
    int number;
    int urgency;
};

ostream &operator<<(ostream &os, const Person &p)
{
    return os << p.number;
}

bool operator==(const Person &p1, const Person &p2)
{
    return p1.number == p2.number && p1.urgency == p2.urgency;
}

class TicketQueue
{
private:
    SeqList<Person> queue;

public:
    TicketQueue(int init_size)
        : queue{ init_size } { }
    void enqueue(const Person &x, int attempts);
    void traverse() { queue.traverse(); }
};

void TicketQueue::enqueue(const Person &x, int attempts)
{
    queue.append(x);
    int index = queue.length() - 1;
    while (index > 0 && queue.visit(index - 1).urgency < x.urgency && attempts > 0)
    {
        swap(queue.visit(index - 1), queue.visit(index));
        --index;
        --attempts;
    }
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
    tq.traverse();
    return 0;
}