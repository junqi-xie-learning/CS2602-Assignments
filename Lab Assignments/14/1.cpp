#include "../../include/graph.h"
using namespace std;
using namespace cs221;

int main()
{
    const char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int n = 0;
    cin >> n;

    Graph<char, int> graph{ n, alphabet };
    for (int i = 0; i < n - 1; ++i)
    {
        char begin = 0;
        int num = 0;
        cin >> begin >> num;
        for (int j = 0; j < num; ++j)
        {
            char end = 0;
            int weight = 0;
            cin >> end >> weight;
            graph.insert(begin, end, weight);
            graph.insert(end, begin, weight);
        }
    }

    SeqList<Pair<char, char>> mst = graph.prim(100);
    int total = 0;
    for (int i = 0; i < mst.length(); ++i)
    {
        Pair<char, char> edge = mst.visit(i);
        total += graph.weight(edge.key, edge.value);
    }
    cout << total;
    return 0;
}