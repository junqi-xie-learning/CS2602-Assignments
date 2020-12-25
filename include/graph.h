#ifndef GRAPH
#define GRAPH

#include "list.h"
#include "queue.h"
#include "priority_queue.h"
#include "disjoint_set.h"
#include "pair.h"

// graph.h
//
// Class: Graph
// Algorithm: Minimal Spanning Tree: Kruskal, Prim
//            Shortest Path: Dijkstra, NegativeDijkstra

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

        void insert(Vertex x, Vertex y, Edge w);
        void remove(Vertex x, Vertex y);
        bool exist(Vertex x, Vertex y) const;
        Edge weight(Vertex x, Vertex y) const;

        void dfs(Vertex x) const;
        void bfs(Vertex x) const;

        SeqList<Pair<Vertex, Vertex>> kruskal() const;
        SeqList<Pair<Vertex, Vertex>> prim(Edge no_edge) const;

        SeqList<Vertex> dijkstra(Vertex start, Vertex end, Edge no_edge) const;
        SeqList<Vertex> negative_dijkstra(Vertex start, Vertex end, Edge no_edge) const;
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
    Edge Graph<Vertex, Edge>::weight(Vertex x, Vertex y) const
    {
        int u = find(x), v = find(y);
        EdgeNode *p = adj_list[u].head;

        while (p && p->end != v)
            p = p->next;
        return p->weight;
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
            for (EdgeNode *p = adj_list[current].head; p; p = p->next)
                if (!visited[p->end])
                    q.enqueue(p->end);
        }
    }

    template <class Vertex, class Edge>
    SeqList<Pair<Vertex, Vertex>> Graph<Vertex, Edge>::kruskal() const
    {
        struct KruskalEdge
        {
            int beg, end;
            Edge weight;

            KruskalEdge(int b = 0, int e = 0, Edge w = Edge{ })
                : beg{ b }, end{ e }, weight{ w } { }
            bool operator<(const KruskalEdge &rp) const { return weight < rp.weight; }
        };

        SeqList<Pair<Vertex, Vertex>> result;
        PriorityQueue<KruskalEdge> pq;
        for (int i = 0; i < vertex_num; ++i)
            for (EdgeNode *p = adj_list[i].head; p; p = p->next)
                if (i < p->end)
                    pq.enqueue({ i, p->end, p->weight });

        int edges = 0;
        DisjointSet ds{ vertex_num };
        while (edges < vertex_num - 1)
        {
            KruskalEdge e = pq.dequeue();
            int u = ds.find(e.beg), v = ds.find(e.end);
            if (u != v)
            {
                ++edges;
                ds.join(u, v);
                result.append({ adj_list[e.beg].ver, adj_list[e.end].ver });
            }
        }
        return result;
    }

    template <class Vertex, class Edge>
    SeqList<Pair<Vertex, Vertex>> Graph<Vertex, Edge>::prim(Edge no_edge) const
    {
        bool *flag = new bool[vertex_num]{ };
        Edge *smallest = new Edge[vertex_num]{ };
        int *start_node = new int[vertex_num]{ };
        for (int i = 0; i < vertex_num; ++i)
            smallest[i] = no_edge;

        SeqList<Pair<Vertex, Vertex>> result;
        int start = 0;
        for (int i = 1; i < vertex_num; ++i)
        {
            for (EdgeNode *p = adj_list[start].head; p; p = p->next)
                if (!flag[p->end] && smallest[p->end] > p->weight)
                {
                    smallest[p->end] = p->weight;
                    start_node[p->end] = start;
                }
            flag[start] = true;

            Edge min = no_edge;
            for (int j = 0; j < vertex_num; ++j)
                if (smallest[j] < min)
                    {
                        min = smallest[j];
                        start = j;
                    }
            result.append({adj_list[start_node[start]].ver, adj_list[start].ver });
            smallest[start] = no_edge;
        }
        delete[] flag;
        delete[] start_node;
        delete[] smallest;
        return result;
    }

    template <class Vertex, class Edge>
    SeqList<Vertex> Graph<Vertex, Edge>::dijkstra(Vertex start, Vertex end, Edge no_edge) const
    {
        Edge *distance = new Edge[vertex_num]{ };
        int *prev = new int[vertex_num]{ };
        bool *known = new bool[vertex_num]{ };
        for (int i = 0; i < vertex_num; ++i)
            distance[i] = no_edge;

        SeqList<Vertex> result;
        int u = find(start), v = find(end);
        distance[u] = 0;
        prev[u] = u;

        for (int i = 1; i < vertex_num; ++i)
        {
            Edge min = no_edge;
            int closest = 0;
            for (int j = 0; j < vertex_num; ++j)
                if (!known[j] && distance[j] < min)
                {
                    min = distance[j];
                    closest = j;
                }
            
            known[closest] = true;
            for (EdgeNode *p = adj_list[closest].head; p; p = p->next)
                if (!known[p->end] && distance[p->end] > min + p->weight)
                {
                    distance[p->end] = min + p->weight;
                    prev[p->end] = closest;
                }
        }

        while (u != v)
        {
            result.insert(0, adj_list[v].ver);
            v = prev[v];
        }
        result.insert(0, adj_list[u].ver);
        return result;
    }

    template <class Vertex, class Edge>
    SeqList<Vertex> Graph<Vertex, Edge>::negative_dijkstra(Vertex start, Vertex end, Edge no_edge) const
    {
        LinkQueue<int> q;
        Edge *distance = new Edge[vertex_num]{ };
        int *prev = new int[vertex_num]{ };
        for (int i = 0; i < vertex_num; ++i)
            distance[i] = no_edge;

        SeqList<Vertex> result;
        int u = find(start), v = find(end);
        distance[u] = 0;
        prev[u] = u;
        q.enqueue(u);

        while (!q.is_empty()) {
            int current = q.dequeue();
            for (typename Graph<Vertex, Edge>::EdgeNode *p = adj_list[current].head; p; p = p->next)
                if (distance[current] + p->weight < distance[p->end])
                {
                    distance[p->end] = distance[current] + p->weight;
                    prev[p->end] = current;
                    q.enqueue(p->end);
                }
        }

        while (u != v)
        {
            result.insert(0, adj_list[v].ver);
            v = prev[v];
        }
        result.insert(0, adj_list[u].ver);
        return result;
    }

} // namespace cs221

#endif