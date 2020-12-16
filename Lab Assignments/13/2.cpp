#include "../../include/graph.h"
using namespace std;
using namespace cs221;


template <class Vertex, class Edge>
class MaxGraph : public Graph<Vertex, Edge>
{
private:
    Vertex find_max(int start, bool visited[]) const;

public:
    MaxGraph(int size, const Vertex d[])
        : Graph<Vertex, Edge>{ size, d } { }
    Vertex find_max(Vertex x) const;
};

template <class Vertex, class Edge>
Vertex MaxGraph<Vertex, Edge>::find_max(Vertex x) const
{
    bool *visited = new bool[this->vertex_num]{ };
    return find_max(this->find(x), visited);
}

template <class Vertex, class Edge>
Vertex MaxGraph<Vertex, Edge>::find_max(int start, bool visited[]) const
{
    typename Graph<Vertex, Edge>::EdgeNode *p = this->adj_list[start].head;
    Vertex larger = this->adj_list[start].ver;
    visited[start] = true;
    while (p)
    {
        if (!visited[p->end])
            larger = max(larger, find_max(p->end, visited));
        p = p->next;
    }
    return larger;
}


int main()
{
    int n = 0, m = 0;
    cin >> n >> m;

    int *vertices = new int[n]{ };
    for (int i = 0; i < n; ++i)
        vertices[i] = i + 1;

    MaxGraph<int, int> graph{ n, vertices };
    for (int i = 0; i < m; ++i)
    {
        int begin = 0, end = 0;
        cin >> begin >> end;
        graph.insert(begin, end);
    }

    for (int i = 0; i < n; ++i)
        cout << graph.find_max(i + 1) << ' ';
}