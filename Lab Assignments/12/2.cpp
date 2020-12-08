#include "../../include/disjoint_set.h"
using namespace std;
using namespace cs221;

class DisjointSetHeight : public DisjointSet
{
private:
    int number;

public:
    DisjointSetHeight(int s)
        : DisjointSet{ s }, number{ 0 } { }

    void join(int root1, int root2);
    int count() const { return number; }
};

void DisjointSetHeight::join(int root1, int root2)
{
    if (root1 == root2)
        return;

    if (parent[root1] == -1 && parent[root2] == -1)
        ++number;
    else if (parent[root1] != -1 && parent[root2] != -1)
        --number;

    if (parent[root1] > parent[root2])
    {
        parent[root2] = min(parent[root2], parent[root1]);
        parent[root1] = root2;
    }
    else if (parent[root1] < parent[root2])
    {
        parent[root1] = min(parent[root1], parent[root2]);
        parent[root2] = root1;
    }
    else
    {
        parent[root2] = min(parent[root2], parent[root1]) - 1;
        parent[root1] = root2;
    }
}

int main()
{
    int n = 0, m = 0;
    cin >> n >> m;

    DisjointSetHeight starry{ n + 1 };
    for (int i = 0; i < m; ++i)
    {
        char op;
        cin >> op;

        int x = 0, y = 0;
        switch (op)
        {
        case 'a':
            cin >> x >> y;
            starry.join(starry.find(x), starry.find(y));
            break;
        
        case 'b':
            cout << starry.count() << endl;
            break;

        case 'c':
            cin >> x >> y;
            cout << (starry.find(x) == starry.find(y) ? "YES" : "NO") << endl;
            break;
        }
    }
    return 0;
}