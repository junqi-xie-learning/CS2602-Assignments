#ifndef DISJOINT_SET
#define DISJOINT_SET

#include <iostream>

// disjoint_set.h:
//
// Class: DisjointSet (for int only)

namespace cs221
{
    class DisjointSet
    {
    protected:
        int size;
        int *parent;

    public:
        DisjointSet(int s);
        ~DisjointSet() { delete[] parent; }

        void join(int root1, int root2);
        int find(int x);
    };

    DisjointSet::DisjointSet(int n)
        : size{ n }, parent{ new int[n] }
    {
        for (int i = 0; i < size; ++i)
            parent[i] = -1;
    }

    void DisjointSet::join(int root1, int root2)
    {
        if (root1 == root2)
            return;
        if (parent[root1] > parent[root2])
        {
            parent[root2] += parent[root1];
            parent[root1] = root2;
        }
        else
        {
            parent[root1] += parent[root2];
            parent[root2] = root1;
        }
    }

    int DisjointSet::find(int x)
    {
        if (parent[x] < 0)
            return x;
        parent[x] = find(parent[x]);
        return parent[x];
    }

} // namespace cs221

#endif