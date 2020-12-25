#include "../../include/graph.h"
using namespace std;
using namespace cs221;

int main()
{
    int n = 0, m = 0;
    cin >> n >> m;
    int start = 0, end = 0;
    cin >> start >> end;

    int *vertices = new int[n]{ };
    for (int i = 0; i < n; ++i)
        vertices[i] = i + 1;

    Graph<int, int> graph{ n, vertices };
    for (int i = 0; i < m; ++i)
    {
        int begin = 0, end = 0, weight = 0;
        cin >> begin >> end >> weight;
        if (!graph.exist(begin, end))
            graph.insert(begin, end, weight);
        if (weight < graph.weight(begin, end))
        {
            graph.remove(begin, end);
            graph.insert(begin, end, weight);
        }
    }

    SeqList<int> result = graph.negative_dijkstra(start, end, INT32_MAX);
    int sum = 0;
    for (int i = 1; i < result.length(); ++i)
    {
        sum += graph.weight(start, result.visit(i));
        start = result.visit(i);
    }
    cout << sum;
    return 0;
}