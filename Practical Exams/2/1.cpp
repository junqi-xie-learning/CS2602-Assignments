#include "../../include/priority_queue.h"
using namespace cs221;
using namespace std;

int main()
{
    int n = 0;
    cin >> n;

    long long int *weight = new long long int[n];
    for (int i = 0; i < n; ++i)
        cin >> weight[i];

    PriorityQueue<long long int> q{ weight, n };
    long long int total = 0;
    while (q.length() != 1)
    {
        long long int min1 = q.dequeue(), min2 = q.dequeue();
        total += min1 + min2;
        q.enqueue(min1 + min2);
    }
    cout << total;
    return 0;
}