#include "../../include/list.h"
#include "../../include/queue.h"
using namespace std;
using namespace cs221;


class NaiveQueue
{
private:
    SeqList<SeqQueue<int> *> queues;
    SeqList<int> ids;

public:
    ~NaiveQueue();

    bool is_empty() const { return queues.length() == 0; }
    void enqueue(int x, int id);
    int dequeue();
};

NaiveQueue::~NaiveQueue()
{
    for (int i = 0; i < queues.length(); ++i)
        delete queues.visit(i);
}

void NaiveQueue::enqueue(int x, int id)
{
    int index = ids.search(id);
    if (index != -1)
        queues.visit(index)->enqueue(x);
    else
    {
        ids.append(id);
        queues.append(new SeqQueue<int>{ } );
        queues.visit(queues.length() - 1)->enqueue(x);
    }
}

int NaiveQueue::dequeue()
{
    int x = queues.visit(0)->dequeue();
    if (queues.visit(0)->is_empty())
    {
        ids.remove(0);
        delete queues.visit(0);
        queues.remove(0);
    }
    return x;
}


int main()
{
    int n = 0;
    cin >> n;

    SeqQueue<int> ids{ n + 1 };
    for (int i = 0; i < n; ++i)
    {
        int id = 0;
        cin >> id;
        ids.enqueue(id);
    }

    NaiveQueue nq;
    int q = 0, no = 1;
    cin >> q;
    for (int i = 0; i < q; ++i)
    {
        int op = 0;
        cin >> op;
        switch (op)
        {
        case 0:
            if (!ids.is_empty())
            {
                nq.enqueue(no, ids.dequeue());
                ++no;
            }
            break;
        case 1:
            if (!nq.is_empty())
                cout << nq.dequeue() << endl;
            else
                cout << -1 << endl;
            break;
        }
    }
    return 0;
}