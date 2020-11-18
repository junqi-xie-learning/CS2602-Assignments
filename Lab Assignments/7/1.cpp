#include "../../include/list.h"
#include "../../include/priority_queue.h"
using namespace std;
using namespace cs221;


class GirlQueue
{
private:
    SeqList<PriorityQueue<int> *> queues;

public:
    GirlQueue(int charms[], int size);

    void merge(int a, int b);
    void enqueue(int a, int b);
    int dequeue(int a);
};

GirlQueue::GirlQueue(int charms[], int size)
    : queues{ size }
{
    for (int i = 0; i < size; ++i)
    {
        queues.append(new PriorityQueue<int>);
        queues.visit(i)->enqueue(charms[i]);
    }
}

void GirlQueue::merge(int a, int b)
{
    while (!queues.visit(b)->is_empty())
        queues.visit(a)->enqueue(queues.visit(b)->dequeue());
    delete queues.visit(b);
    queues.visit(b) = nullptr;
}

void GirlQueue::enqueue(int a, int b)
{
    queues.visit(a)->enqueue(b);
}

int GirlQueue::dequeue(int a)
{
    if (queues.visit(a)->is_empty())
        return -1;
    return queues.visit(a)->dequeue();
}


int main()
{
    int N = 0, M = 0;
    cin >> N >> M;

    int charms[N];
    for (int i = 0; i < N; ++i)
        cin >> charms[i];
    
    GirlQueue gq{ charms, N };
    for (int i = 0; i < M; ++i)
    {
        int op = 0, a = 0, b = 0;
        cin >> op;
        switch (op)
        {
        case 0:
            cin >> a >> b;
            gq.merge(a, b);
            break;
        case 1:
            cin >> a;
            cout << gq.dequeue(a) << endl;
            break;
        case 2:
            cin >> a >> b;
            gq.enqueue(a, b);
            break;
        }
    }
    return 0;
}