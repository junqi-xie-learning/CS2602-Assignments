#include "../../include/graph.h"
using namespace std;
using namespace cs221;

template <class Vertex, class Edge>
class PathGraph : public Graph<Vertex, Edge>
{
private:
    int find_path(int start, bool visited[], int length) const;

public:
    PathGraph(int size, const Vertex d[])
        : Graph<Vertex, Edge>{ size, d } { }
    int find_path(Vertex start, int length) const;
};

template <class Vertex, class Edge>
int PathGraph<Vertex, Edge>::find_path(Vertex start, int length) const
{
    bool *visited = new bool[this->vertex_num]{ };
    return find_path(this->find(start), visited, length);
}

template <class Vertex, class Edge>
int PathGraph<Vertex, Edge>::find_path(int start, bool visited[], int length) const
{
    if (length == 0)
        return 1;
    
    typename Graph<Vertex, Edge>::EdgeNode *p = this->adj_list[start].head;
    int path = 0;
    visited[start] = true;
    while (p)
    {
        if (!visited[p->end])
            path += find_path(p->end, visited, length - 1);
        p = p->next;
    }
    visited[start] = false;
    return path;
}


int main()
{
    int n = 0, m = 0;
    cin >> n >> m;
    int start = 0, length = 0;
    cin >> start >> length;

    int *vertices = new int[n]{ };
    for (int i = 0; i < n; ++i)
        vertices[i] = i + 1;

    PathGraph<int, int> graph{ n, vertices };
    for (int i = 0; i < m; ++i)
    {
        int begin = 0, end = 0;
        cin >> begin >> end;
        if (!graph.exist(begin, end))
            graph.insert(begin, end, 1);
    }

    cout << graph.find_path(start, length) << endl;
    return 0;
}