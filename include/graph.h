#ifndef GRAPH
#define GRAPH

#include "queue.h"

// graph.h
//
// Class: Graph

namespace cs221
{
    template <class Vertex, class Edge>
    class Graph
    {
    protected:
        struct EdgeNode
        {
            int end;
            Edge weight;
            EdgeNode *next;
            EdgeNode(int e, Edge w, EdgeNode *n = nullptr)
                : end{ e }, weight{ w }, next{ n } { }
        };

        struct VertexNode
        {
            Vertex ver;
            EdgeNode *head;
            VertexNode(EdgeNode *h = nullptr)
                : head{ h } { }
        };

        VertexNode *adj_list;
        int vertex_num, edge_num;

        int find(Vertex v) const;
        void dfs(int start, bool visited[]) const;
        void bfs(int start, bool visited[]) const;

    public:
        Graph(int size, const Vertex d[]);
        ~Graph();

        void insert(Vertex x, Vertex y, Edge w = Edge{ });
        void remove(Vertex x, Vertex y);
        bool exist(Vertex x, Vertex y) const;

        void dfs(Vertex x) const;
        void bfs(Vertex x) const;
    };

    template <class Vertex, class Edge>
    int Graph<Vertex, Edge>::find(Vertex v) const
    {
        for (int i = 0; i < vertex_num; ++i)
            if (adj_list[i].ver == v)
                return i;
        return -1;
    }

    template <class Vertex, class Edge>
    Graph<Vertex, Edge>::Graph(int size, const Vertex d[])
        : vertex_num{ size }, edge_num{ 0 }, adj_list{ new VertexNode[size] }
    {
        for (int i = 0; i < vertex_num; ++i)
            adj_list[i].ver = d[i];
    }

    template <class Vertex, class Edge>
    Graph<Vertex, Edge>::~Graph()
    {
        for (int i = 0; i < vertex_num; ++i)
        {
            EdgeNode *p = adj_list[i].head;
            while (p)
            {
                EdgeNode *tmp = p;
                p = p->next;
                delete tmp;
            }
        }
        delete[] adj_list;
    }

    template <class Vertex, class Edge>
    void Graph<Vertex, Edge>::insert(Vertex x, Vertex y, Edge w)
    {
        int u = find(x), v = find(y);
        adj_list[u].head = new EdgeNode{ v, w, adj_list[u].head };
        ++edge_num;
    }

    template <class Vertex, class Edge>
    void Graph<Vertex, Edge>::remove(Vertex x, Vertex y)
    {
        int u = find(x), v = find(y);
        EdgeNode *p = adj_list[u].head;

        if (!p)
            return;
        if (p->end == v)
        {
            adj_list[u].head = p->next;
            delete p;
            --edge_num;
            return;
        }

        while (p->next && p->next->end != v)
            p = p->next;
        if (p->next)
        {
            EdgeNode *q = p->next;
            p->next = q->next;
            delete q;
            --edge_num;
        }
    }

    template <class Vertex, class Edge>
    bool Graph<Vertex, Edge>::exist(Vertex x, Vertex y) const
    {
        int u = find(x), v = find(y);
        EdgeNode *p = adj_list[u].head;

        while (p && p->end != v)
            p = p->next;
        return p;
    }

    template <class Vertex, class Edge>
    void Graph<Vertex, Edge>::dfs(Vertex x) const
    {
        bool *visited = new bool[vertex_num]{ };
        dfs(find(x), visited);
        for (int i = 0; i < vertex_num; ++i)
        {
            if (visited[i])
                continue;
            dfs(i, visited);
            std::cout << std::endl;
        }
    }

    template <class Vertex, class Edge>
    void Graph<Vertex, Edge>::dfs(int start, bool visited[]) const
    {
        EdgeNode *p = adj_list[start].head;
        std::cout << adj_list[start].ver << ' ';
        visited[start] = true;
        while (p)
        {
            if (!visited[p->end])
                dfs(p->end, visited);
            p = p->next;
        }
    }

    template <class Vertex, class Edge>
    void Graph<Vertex, Edge>::bfs(Vertex x) const
    {
        bool *visited = new bool[vertex_num]{ };
        bfs(find(x), visited);
        for (int i = 0; i < vertex_num; ++i)
        {
            if (visited[i])
                continue;
            bfs(i, visited);
            std::cout << std::endl;
        }
    }

    template <class Vertex, class Edge>
    void Graph<Vertex, Edge>::bfs(int start, bool visited[]) const
    {
        LinkQueue<int> q;
        q.enqueue(start);
        while (!q.is_empty())
        {
            int current = q.dequeue();
            if (visited[current])
                continue;
            
            std::cout << adj_list[current].ver << ' ';
            visited[current] = true;
            EdgeNode *p = adj_list[current].head;
            while (p)
            {
                if (!visited[p->end])
                    q.enqueue(p->end);
                p = p->next;
            }
        }
    }

} // namespace cs221

#endif